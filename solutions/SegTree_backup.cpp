#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e6 + 5;
const int MOD = 1e9 + 7;

vector<int> tree(4 * MAXN, 0);


struct SegTree {

    int n;
    int size;
    vector<int> tree;

    SegTree (int n) {
        this->n = n;
        this->size = 4 * n;
        this->tree.resize(this->size, INT_MIN);
    }

    void
    update(int v, int l, int r, int position, int value)
    {
        if (l + 1 == r) {
            this->tree[v] = value;
        } else {
            int m = (l + r) / 2;
            if (position < m) {
                update(2 * v + 1, l, m, position, value);
            } else {
                update(2 * v + 2, m, r, position, value);
            }
            this->tree[v] = max(this->tree[2 * v + 1], this->tree[2 * v + 2]);
        }
    }


    int
    get_max(int v, int l, int r, int ql, int qr)
    {
        if (r <= ql || qr <= l) {
            return INT_MIN;
        } else if (ql <= l && r <= qr) {
            return this->tree[v];
        } else {
            int m = (l + r) / 2;
            return max(get_max(2 * v + 1, l, m, ql, qr), get_max(2 * v + 2, m, r, ql, qr));
        }
    }
};


int
main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int base, prev = 0, buf; cin >> base;
    buf = 1;
    SegTree T(n);
    for (int i = 0; i < n; i++) {
        buf = ((prev + buf * base) % MOD + MOD) % MOD;
        prev = buf;
        T.update(0, 0, n, i, buf);
    }
 
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int type; cin >> type;
        int l, r; cin >> l >> r;
        if (type == 1) {
            l = l % n; r = r % n;
            if (l > r) {
                swap(l, r);
            }
            r++;
            std::cout << T.get_max(0, 0, n, l, r);
        } else {
            l = l % n;
            T.update(0, 0, n, l, r);
        }
    }
 
    return 0;
}
