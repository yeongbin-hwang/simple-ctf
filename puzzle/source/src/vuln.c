#include <stdio.h>
#include <string.h>
#include <seccomp.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>

const char *src_str = "\
#include <stdio.h>\n\
\n\
int main() {\n\
    char *quote;\n\
    int val[2];\n\
    int *val_ptr = &val[0];\n\
\n\
    val[0] = 8;\n\
    val[1] = 9;\n\
    val[0] += val[1];\n\
    val[1] -= val[0];\n\
    val[1] = ~val[1];\n\
    val[1] &= 0xf;\n\
    val[0] /= val[1];\n\
    val[1] = (val[0] > 1)? val[1]^val[0] : 'a'|val[1];\n\
\n\
    switch (*val_ptr) {\n\
        case 0:\n\
            quote = \"two driven jocks help fax my big quiz.\";\n\
            break;\n\
        case 1:\n\
            quote = \"FICKLE JINX BOG DWARVES SPY MATH QUIZ.\";\n\
            break;\n\
        case 2:\n\
            quote = \"public junk dwarves hug my quartz fox.\";\n\
            break;\n\
        case 3:\n\
            quote = \"QUICK FOX JUMPS NIGHTLY ABOVE WIZARD.\";\n\
            break;\n\
        case 4:\n\
            quote = \"five quacking zephyrs jolt my wax bed.\";\n\
            break;\n\
        case 5:\n\
            quote = \"THE FIVE BOXING WIZARDS JUMP QUICKLY.\";\n\
            break;\n\
        case 6:\n\
            quote = \"pack my box with five dozen liquor jugs.\";\n\
            break;\n\
        case 7:\n\
            quote = \"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.\";\n\
            break;\n\
        case 8:\n\
            quote = \"when zombies arrive, quickly fax judge pat.\";\n\
            break;\n\
        case 9:\n\
            quote = \"WOVEN SILK PYJAMAS EXCHANGED FOR BLUE QUARTZ.\";\n\
            break;\n\
        default:\n\
            quote = \"Noticed?@`\";\n\
            break;\n\
    }\n\
    printf(\"%1$s\\n\", quote);\n\
    return 0;\n\
}\n\
";

char in[0x1000];

void setup_rules() {
  // Init the filter
  scmp_filter_ctx ctx;
  ctx = seccomp_init(SCMP_ACT_KILL); // default action: kill
  if (ctx == NULL)
    exit(-1);

  // setup basic whitelist
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigreturn), 0) < 0)
    exit(-1);
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) < 0)
    exit(-1);
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0) < 0)
    exit(-1);
  if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) < 0)
    exit(-1);
  if (seccomp_load(ctx) < 0)
    exit(-1);
}

void start() {
  char buf[200];
  strcpy(buf, in);
  memset(in, 0, sizeof(in));
}

int main(int argc, char** argv) {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("We have a source code:\n");
  puts(src_str);
  puts("check");
  fgets(in, sizeof(in), stdin);
  setup_rules();
  start();
}
