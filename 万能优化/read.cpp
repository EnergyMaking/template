char buf[1 << 15], *fs, *ft;
inline char getc() {
	return (ft == fs && (ft = (fs = buf) + fread(buf, 1, 1 << 15, stdin), ft == fs)) ? 0 : *fs++;
}
inline int read(int &x) {
	x = 0;
	int f = 1;
	char ch = getc();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getc();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getc();
	}
	return x;
}
