struct segment {
    struct tree {
        int l, r;
        ll lt, val;
    };
    tree node[N << 2];

    void build(int p, int l, int r) {
        node[p] = (tree) {
            l, r
        };

        if (l == r) {
            node[p].val = 1ll * a[l];
            return;
        }

        int mid = l + r >> 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
        node[p].val = node[lson].val + node[rson].val;
    }
    void pushdown(int p) {
        if (node[p].lt) {
            node[lson].val += (node[lson].r - node[lson].l + 1) * node[p].lt;
            node[rson].val += (node[rson].r - node[rson].l + 1) * node[p].lt;
            node[lson].lt += node[p].lt;
            node[rson].lt += node[p].lt;
            node[p].lt = 0;
        }
    }
    void pushup(int p) {
        node[p].val = node[lson].val + node[rson].val;
    }
    void modify(int p, int l, int r, ll d) {
        if (l <= node[p].l && node[p].r <= r) {
            node[p].lt += d;
            node[p].val += d * (node[p].r - node[p].l + 1);
            return;
        }

        pushdown(p);
        int mid = node[p].l + node[p].r >> 1;

        if (l <= mid)
            modify(lson, l, r, d);

        if (r > mid)
            modify(rson, l, r, d);

        pushup(p);
    }
    ll get(int p, int l, int r) {
        ll ans = 0;

        if (l <= node[p].l && node[p].r <= r)
            return node[p].val;

        pushdown(p);
        int mid = node[p].l + node[p].r >> 1;

        if (l <= mid)
            ans += get(lson, l, r);

        if (r > mid)
            ans += get(rson, l, r);

        return ans;
    }
};
segment tr;
