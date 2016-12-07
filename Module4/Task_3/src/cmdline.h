struct command {
    char com;
    char *param;
};

int parse_cmdline(char ***argv, char *input);
struct command *find_options(int argc, char **argv);
