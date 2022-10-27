#include <bits/stdc++.h>

using namespace std;


int
max(int x, int y)
{
    if (x < y) {
        return y;
    } else {
        return x;
    }
}


int
min(int x, int y)
{
    if (x < y) {
        return x;
    } else {
        return y;
    }
}


struct SSTNode {
    int data, bsize;
    vector<SSTNode *> sons;

    SSTNode(int data, int len)
    {
        this->data = data;
        this->sons.resize(max(2, (int)log(len)), nullptr);
        this->bsize = (len + (int)this->sons.size() - 1) / ((int)this->sons.size());
    }

    int
    get_max(int l, int r, int ql, int qr)
    {
        if (r <= ql || qr <= l) {
            return INT_MIN;
        } else if (ql <= l && r <= qr) {
            return this->data;
        } else {
            int result = INT_MIN;
            for (int i = 0; i < (int)this->sons.size(); ++i) {
                result = max(result, this->sons[i]->get_max(l + i * this->bsize, min(l + (i + 1) * this->bsize, r), ql, qr));
            }
            return result;
        }
    }

    void
    update_list(int l, int r, int position, int value)
    {
        if (l + 1 == r) {
            this->data = value;
        } else {
            int block = (position - l) / this->bsize;
            this->sons[block]->update_list(l + block * this->bsize, min(l + (block + 1) * this->bsize, r), position, value);
            this->data = max(this->data, this->sons[block]->data);
        }
    }

    void
    update(int l, int r, int position, int value)
    {
        if (l + 1 == r) {
            this->data = value;
        } else {
            int block = (position - l) / this->bsize;
            this->sons[block]->update(l + block * this->bsize, l + (block + 1) * this->bsize, position, value);
            this->data = INT_MIN;
            for (int i = 0; i < (int)this->sons.size(); ++i) {
                this->data = max(this->data, this->sons[i]->data);
            }
        }
    }

    ~SSTNode()
    {
        for (int i = 0; i < (int)sons.size(); ++i) {
            delete sons[i];
        }
    }
};


SSTNode *
build(int l, int r)
{
    SSTNode *root = new SSTNode(INT_MIN, r - l);
    if (l + 1 < r) {
        for (int i = 0; i < (int)root->sons.size(); ++i) {
            root->sons[i] = build(l + i * root->bsize, min(l + (i + 1) * root->bsize, r));
        }
    }
    return root;
}


int
main(void )
{
    int n, base, buf; cin >> n >> base;
    //int prev = 0;

    SSTNode *root = build(0, n);

    buf = 1;
    for (int i = 0; i < n; i++) {
        //buf = ((prev + buf * base) % MOD + MOD) % MOD;
        cin >> buf;
        //prev = buf;
        root->update_list(0, n, i, buf);
    }


    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int type; cin >> type;
        int l, r; cin >> l >> r;
        l--;
        if (type == 1) {
            cout << root->get_max(0, n, l, r) << '\n';
        } else {
            root->update(0, n, l, r);
        }
    }

    return 0;
}

