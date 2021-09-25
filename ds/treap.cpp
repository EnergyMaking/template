#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;

int T;

struct treap {
    int tot, root;
    struct tree {
        int l, r;
        int val, dat;
        int cnt, size;
    };
    tree node[100005];
    
    int new_node(int val) {
        node[++tot].val = val;
        node[tot].dat = rand();
        node[tot].cnt = node[tot].size = 1;
        return tot;
    }
    void pushup(int p) {
        node[p].size = node[node[p].l].size + node[node[p].r].size + node[p].cnt;
    }
    void build() {
        srand(time(0));
        new_node(-0x3f3f3f3f);
        new_node(0x3f3f3f3f);
        root = 1, node[root].r = 2;
        pushup(root);
    }
    int get_rank_by_val(int p, int val) {
        if (!p) return 0;
        if (val == node[p].val) return node[node[p].l].size + 1;
        if (val < node[p].val) return get_rank_by_val(node[p].l, val);
        return get_rank_by_val(node[p].r, val) + node[node[p].l].size + node[p].cnt;
    }
    int get_val_by_rank(int p, int rank) {
        if (!p) return 0x3f3f3f3f;
        if (node[node[p].l].size >= rank) return get_val_by_rank(node[p].l, rank);
        if (node[node[p].l].size + node[p].cnt >= rank) return node[p].val;
        return get_val_by_rank(node[p].r, rank - node[node[p].l].size - node[p].cnt);
    }
    void zig(int &p) {
        int q = node[p].l;
        node[p].l = node[q].r, node[q].r = p, p = q;
        pushup(node[p].r), pushup(p);
    }
    void zag(int &p) {
        int q = node[p].r;
        node[p].r = node[q].l, node[q].l = p, p = q;
        pushup(node[p].l), pushup(p);
    }
    void insert(int &p, int val) {
        if (!p) {
            p = new_node(val);
            return;
        }
        if (val == node[p].val) {
            node[p].cnt++;
            pushup(p);
            return;
        }
        if (val < node[p].val) {
            insert(node[p].l, val);
            if (node[p].dat < node[node[p].l].dat) zig(p);
        }
        else {
            insert(node[p].r, val);
            if (node[p].dat < node[node[p].r].dat) zag(p);
        }
        pushup(p);
    }
    int get_pre(int val) {
        int ans = 1, p = root;
        while (p) {
            if (val == node[p].val) {
                if (node[p].l > 0) {
                    p = node[p].l;
                    while (node[p].r > 0) p = node[p].r;
                    ans = p;
                }
                break;
            }
            if (node[p].val < val && node[p].val > node[ans].val) ans = p;
            if (val < node[p].val) p = node[p].l;
            else p = node[p].r;
        }
        return node[ans].val;
    }
    int get_nxt(int val) {
        int ans = 2, p = root;
        while (p) {
            if (val == node[p].val) {
                if (node[p].r > 0) {
                    p = node[p].r;
                    while (node[p].l > 0) p = node[p].l;
                    ans = p;
                }
                break;
            }
            if (node[p].val > val && node[p].val < node[ans].val) ans = p;
            if (val < node[p].val) p = node[p].l;
            else p = node[p].r;
        }
        return node[ans].val;
    }
    void del(int &p, int val) {
        if (!p) return; 
        if (val == node[p].val) {
            if (node[p].cnt > 1) {
                node[p].cnt--;
                pushup(p);
                return;
            }
            if (node[p].l || node[p].r) {
                if (!node[p].r || node[node[p].l].dat > node[node[p].r].dat) {
                    zig(p);
                    del(node[p].r, val);
                }
                else {
                    zag(p);
                    del(node[p].l, val);
                }
                pushup(p);
            }
            else p = 0;
            return;
        }
        if (val < node[p].val) del(node[p].l, val);
        else del(node[p].r, val);
        pushup(p);
    }
};
treap tr;

int main() {
    scanf("%d", &T);
    tr.build();
    while (T--) {
        int opt, x;
        scanf("%d %d", &opt, &x);
        if (opt == 1) tr.insert(tr.root, x);
        else if (opt == 2) tr.del(tr.root, x);
        else if (opt == 3) printf("%d\n", tr.get_rank_by_val(tr.root, x) - 1);
        else if (opt == 4) printf("%d\n", tr.get_val_by_rank(tr.root, x + 1));
        else if (opt == 5) printf("%d\n", tr.get_pre(x));
        else printf("%d\n", tr.get_nxt(x));
    }
    return 0;
}
