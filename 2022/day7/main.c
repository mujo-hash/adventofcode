#include <err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 64

struct file {
	size_t size;
	char name[MAX];
};

struct dir {
	struct dir *prev;
	char name[MAX];
	struct file **files;
	int nfiles;
	struct dir **dirs;
	int ndirs;
};

struct tree {
	struct dir *root;
	struct dir *cwd;
};

void pindent(int depth) {
	int i;

	for (i = 0; i < depth; i++)
		printf("  ");
}

void pdir(struct dir *dir, int depth) {
	int i;
 
	pindent(depth);
	printf("- %s (dir)\n", dir->name);
	for (i = 0; i < dir->ndirs; i++) {
		pdir(dir->dirs[i], depth + 1);
	}
	for (i = 0; i < dir->nfiles; i++) {
		pindent(depth + 1);
		printf("- %s (file, size=%ld)\n",
			dir->files[i]->name,
			dir->files[i]->size
		);
	}
}

void ptree(struct tree *tree) {
	int i;

	if (tree->root == NULL)
		return;

	printf("- %s (dir)\n", tree->root->name);
	for (i = 0; i < tree->root->ndirs; i++) {
		pdir(tree->root->dirs[i], 1);
	}
	for (i = 0; i < tree->root->nfiles; i++) {
		printf("  - %s (file, size=%ld)\n",
			tree->root->files[i]->name,
			tree->root->files[i]->size
		);
	}
}

struct dir *mkdir(char *name, struct dir *prev) {
	struct dir *p;

	p = malloc(sizeof(struct dir));
	p->prev = prev;
	strncpy(p->name, name, MAX); // I wish linux had strlcpy...
	p->files = NULL;
	p->nfiles = 0;
	p->dirs = NULL;
	p->ndirs = 0;

	return p;
}

struct dir *finddir(struct tree *tree, char *name) {
	int i;

	if (tree->root == NULL)
		return NULL;

	if (strncmp(name, "..", 2) == 0)
		return tree->cwd->prev;

	for (i = 0; i <= tree->cwd->ndirs; i++) {
		if (strncmp(tree->cwd->dirs[i]->name, name, MAX) == 0)
			return tree->cwd->dirs[i];
	}
	err(1, "finddir");
}

void parsecd(struct tree *tree, char *dir) {
	struct dir *p;

	// trim newline
	dir[strlen(dir) - 1] = '\0';

	if ((p = finddir(tree, dir)) != NULL) {
		tree->cwd = p;
	} else if (dir[0] == '/') {	// assuming no cd's with absolute paths
		p = mkdir(dir, NULL);
		tree->root = p;
		tree->cwd = p;
	} else {
		err(1, "finddir");
	}
}

void parsecmd(struct tree *tree, char *line) {
	char *tok, *str;

	str = line;
	tok = strsep(&str, " ");
	if (tok[0] != '$')
		err(1, "parsecmd");

	tok = strsep(&str, " ");
	if (strncmp(tok, "cd", 2) == 0) {
		parsecd(tree, str);
	} else if (strncmp(tok, "ls", 2) == 0) {
		// do nothing
	} else {
		err(1, "unknown command");
	}
}

void mkdirs(struct tree *tree) {
	struct dir **p;

	if (tree->cwd->dirs == NULL) {
		p = calloc(sizeof(struct dir *), MAX);
		tree->cwd->dirs = p;
	} else {
		err(1, "mkdirs");
	}
}

void mkfiles(struct tree *tree) {
	struct file **p;

	if (tree->cwd->files == NULL) {
		p = calloc(sizeof(struct file *), MAX);
		tree->cwd->files = p;
	} else {
		err(1, "mkfiles");
	}
}

void parseout(struct tree *tree, char *line) {
	char *tok, *str;

	str = line;
	tok = strsep(&str, " ");
	if (tok[0] == '$')
		err(1, "parseout");

	if (strncmp(tok, "dir", 3) == 0) {
		struct dir *p;

		tok = strsep(&str, " \n");
		p = mkdir(tok, tree->cwd);
		if (tree->cwd->dirs == NULL)
			mkdirs(tree);
		tree->cwd->dirs[tree->cwd->ndirs++] = p;
	} else {
		struct file *p;

		if (tree->cwd->files == NULL)
			mkfiles(tree);
		p = malloc(sizeof(struct file));
		p->size = atol(tok);
		tok = strsep(&str, " \n");
		strncpy(p->name, tok, MAX);
		tree->cwd->files[tree->cwd->nfiles++] = p;
	}
}

void parse(struct tree *tree, char *line) {
	switch(line[0]) {
		case '$': parsecmd(tree, line); break;
		default: parseout(tree, line); break;
	}
}

int main() {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	struct tree tree = { NULL, NULL };

	while ((nread = getline(&line, &len, stdin)) != -1) {
		parse(&tree, line);
	}
	ptree(&tree);
	free(line);
	return 0;
}
