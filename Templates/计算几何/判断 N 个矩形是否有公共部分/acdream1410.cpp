const int co = 777;

LL po[N];

struct seg{
    int l, r, sz; LL f, g;
    int mid(){
        return l + r >> 1;
    }
} tree[N << 2];

void init_tree(int l, int r, int x){
    tree[x].l = l, tree[x].r = r, tree[x].sz = r - l + 1;
    if(l == r) return;
    int mid = l + r >> 1;
    init_tree(l, mid, lc(x));
    init_tree(mid + 1, r, rc(x));
}

void insert(int pos, int x){
    if(tree[x].l == tree[x].r){
        tree[x].f = tree[x].g = 1;
        return;
    }
    int mid = tree[x].mid();
    if(pos <= mid) insert(pos, lc(x));
    else insert(pos, rc(x));
    tree[x].f = (tree[lc(x)].f * po[tree[rc(x)].sz] + tree[rc(x)].f);
    tree[x].g = (tree[rc(x)].g * po[tree[lc(x)].sz] + tree[lc(x)].g);
}

LL query(int l, int r, int x, int id){
    if(l <= tree[x].l && tree[x].r <= r){
        if(id == 1) return tree[x].f;
        return tree[x].g;
    }
    int mid = tree[x].mid(); LL res;
    if(id == 1){
        if(l <= mid && r > mid) res = query(l, r, lc(x), id) * po[min(tree[x].r, r) - mid] + query(l, r, rc(x), id);
        else if(l <= mid) res = query(l, r, lc(x), id);
        else res = query(l, r, rc(x), id);
    }
    if(id == 2){
        if(l <= mid && r > mid) res = query(l, r, rc(x), id) * po[mid - max(tree[x].l, l) + 1] + query(l, r, lc(x), id);
        else if(l <= mid) res = query(l, r, lc(x), id);
        else res = query(l, r, rc(x), id);
    }
    return res;
}

int n, x;

int main(){
    //freopen("in.txt", "r", stdin);
    po[0] = 1;
    for(int i = 1; i < N; i ++)
        po[i] = po[i - 1] * co;
    cin >> n;
    init_tree(1, n, 1);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &x);
        insert(x, 1);
        int mn = max(1, 2 * x - n);
        int mx = min(n, 2 * x - 1);
        //cout << mn << ' ' << x << ' ' << mx << endl;
        //cout << query(mn, x, 1, 1) << ' ' << query(x, mx, 1, 2) << endl;
        if(query(mn, x, 1, 1) != query(x, mx, 1, 2)){
            puts("YES");
            return 0;
        }
    }
    puts("NO");
}
