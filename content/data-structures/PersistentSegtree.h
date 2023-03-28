/**
 * Author: BForBruteForce
 * License: CC0
 * Description: Persistent segment tree.
 * Status: stress-tested
*/

const int N = 2e5 + 1;
struct node{
	ll count;
	node *l, *r;
	node(ll a=0, node* b=0, node* c=0) {
		count = a, l = b, r = c;
	}
	node* update(int, int, int, ll);
};
node* nil() {
	node *x = new node();
	x->r = x->l = x;
	return x;
}
node* node::update(int l, int r, int idx, ll val){
	if(idx < l || idx > r) return this;
	if(l == r){
        ll add = this ? this->count : 0;
	    return new node(val + add, nil(), nil());
	}
	int m = (l + r) / 2;
	node* left, *right;
	left = this->l->update(l, m, idx, val);
	right = this->r->update(m + 1, r, idx, val);
	return new node((left->count)+(right->count),left,right);     
}
ll query(node* a, int tl, int tr, int l, int r){
    if(tl == l && tr == r) return a->count;
    if(l > r) return 0;
    int tm = (tl + tr) / 2;
    int left, right;
    left = query(a->l, tl, tm, l, min(r, tm));
    right = query(a->r, tm + 1, tr, max(l, tm + 1), r);
    return left + right;
}
node *root[N];