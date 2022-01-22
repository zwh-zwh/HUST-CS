#define  _CRT_SECURE_NO_WARNINGS
#include "fun.h"
#include <iostream>
#include <cmath>

POINT* TOTAL::point = 0;
LINE* TOTAL::line = 0;
int TOTAL::cnt_line = 0;
int TOTAL::cnt_point = 0;
int TOTAL::obs = 0;
MAT TOTAL::raw;
MAT TOTAL::tra;

POINT::POINT(int n, int x, int y): num(n), x(x), y(y) { }
int& POINT::getx() {
    return x;
}
int& POINT::gety() {
    return y;
}
int& POINT::getnum() {
    return num;
}


LINE::LINE(int num, int count, int* stop) : num(num), stop(count ? new int[count] : 0), count(stop ? count : 0) {
    if (LINE::stop == 0 && count != 0)
        return;
    for (int x = 0; x < count; x++)
        LINE::stop[x] = stop[x];
}
LINE::LINE(const LINE& r): num(r.num), stop(r.count?new int[r.count]:0), count(stop ? r.count : 0) {
    if (stop == 0 && r.count != 0)
        return;
    for (int x = 0; x < count; x++)
        stop[x] = r.stop[x];
}
LINE::LINE(LINE&& r) noexcept: num(r.num), stop(r.stop), count(r.count) {
    (int&)(r.num) = (int&)(r.count)=0;
    (int*&)(r.stop) = 0;
}
LINE& LINE::operator=(const LINE& r) {
    if (this == &r) return *this;
    if (stop) { delete[] stop; }
    (int&)num = r.num;
    (int*&)stop = new int[r.count];
    (int&)count = stop ? r.count : 0;
    for (int x = 0; x < count; x++)
        stop[x] = r.stop[x];
    return *this;
}
LINE& LINE::operator=(LINE&& r)noexcept{
    if (this == &r) return *this;
    if (stop) { delete[] stop; }
    (int&)num = r.num;
    (int*&)stop = r.stop;
    (int&)count = r.count;
    (int&)(r.num) = (int&)(r.count) = 0;
    (int*&)(r.stop) = 0;
    return *this;
}
int LINE::has(int s)const {
    for (int x = 0; x < count; x++)
        if (stop[x] == s) return x;
    return -1;
}
int LINE::cross(const LINE& b)const {  //线路相交则返回1
    if (this == &b) return 0;
    for (int x = 0; x < count; x++)
        if (b.has(stop[x]) != -1) return 1;
    return 0;
}
LINE::operator  int () const{
    return num;
}      //取线路编号
int LINE::COUNT()const {
    return count;
}         //取站点数目
int& LINE::operator[](int x) {
    return stop[x];
}    //第x站的站点编号
LINE::~LINE()noexcept {
    if (stop) {
        delete[] stop;
        (int*&)stop = 0;
        (int&)num = (int&)count = 0;
    }
}


CROSS::CROSS(int begin, int end, int stop): begin(begin), end(end), stop(stop) { }
int CROSS::operator==(const CROSS& t)const {
    return begin == t.begin && end == t.end && stop == t.stop;
}
int& CROSS::getbegin() {
    return begin;
}
int& CROSS::getend() {
    return end;
}
int& CROSS::getpoint() {
    return stop;
}


OPTION::OPTION(CROSS* tran, int noft): cross(noft?new CROSS[noft]:0), count(tran ? noft : 0) {
    if (cross == 0 && noft!=0)
        return;
    for (int x = 0; x < noft; x++)
        cross[x] = tran[x];
}
OPTION::OPTION(const CROSS& t): cross(new CROSS[1]), count(cross ? 1 : 0) {
    if (cross == 0)
        return;
    *cross = t;
}
OPTION::OPTION(const OPTION& r): cross(r.count?new CROSS[r.count]:0), count(cross ? r.count : 0) {
    if (cross == 0 && r.count!=0)
        return;
    for (int x = 0; x < count; x++)
        cross[x] = r.cross[x];
}
OPTION::OPTION(OPTION&& r) noexcept : cross(r.cross), count(r.count) {
    (CROSS*&)(r.cross) = 0;
    (int&)(r.count)=0;
}
OPTION::~OPTION() noexcept {
    if (cross) {
        delete[]cross;
        (CROSS*&)cross = 0;
        *(int*)&count = 0;
    }
}
int OPTION::print()const {
    for (int x = 0; x < count; x++)
        if (cross[x].getpoint() == -1)
            printf("\tstay on line %d and go directly\n", cross[x].getbegin() + 1);
        else
            printf("\tfrom line %d to line %d via %d\n", cross[x].getbegin() + 1, cross[x].getend() + 1, cross[x].getpoint() + 1);
    return count;
}
OPTION::operator int()const {
    return count;
}


OPTION OPTION::operator *()const { //去重复转乘
    int cnt = count;
    CROSS* t = new CROSS[count];
    for (int x = 0; x < cnt; x++) t[x] = cross[x];
    for(int x=0; x<cnt-1; x++)
        for (int y = x + 1; y < cnt; y++) {
            if (t[x].getpoint() == t[y].getpoint()&&t[x].getbegin() == t[y].getend()) { //循环了
                for (int m=x,n=y+1; n <cnt; n++, m++)
                    t[m] = t[n];
                cnt -= (y+1 - x);
                y = x;
            }
        }
    OPTION r(t, cnt);
    delete[]t;
    return r;
}
int OPTION::operator==(const OPTION& r)const {
    int m = 1;
    if (count != r.count)
        return 0;
    for (int x = 0; x < count; x++) {
        if (cross[x] == r.cross[x])
            continue;
        m = 0;
        break;
    }
    return m;
}
CROSS& OPTION::operator[](int x) { //一条线路上所有转乘
    if (x<0 || x>count)
        throw"error";
    return cross[x];
}
OPTION  OPTION::operator+(const OPTION& r)const { //两段路径连接
    int x, y;
    OPTION s;
    if (count == 0) return *this;
    if (r.count == 0) return r;
    if (cross[count - 1].getend() != r.cross[0].getbegin())
        return *this;
    (CROSS*&)(s.cross) = new CROSS[count + r.count];
    (int&)(s.count) = s.cross ? count + r.count : 0;
    for (x = 0; x < count; x++) s.cross[x] = cross[x];
    for (y = 0; y < r.count; y++) s.cross[x++] = r.cross[y];
    return *s;
}
OPTION& OPTION::operator=(const OPTION& r) {
    if (this == &r) return *this;
    if (cross) delete[]cross;
    (CROSS*&)cross = new CROSS[r.count];
    (int&)count = cross ? r.count : 0;
    for (int x = 0; x < count; x++) cross[x] = r.cross[x];
    return *this;
}
OPTION& OPTION::operator=(OPTION&& r) noexcept{
    if (this == &r) return *this;
    if (cross) delete[]cross;
    (CROSS*&)cross =r.cross;
    (int&)count = r.count;
    (CROSS*&)(r.cross) = nullptr;
    (int&)(r.count) = 0;
    return *this;
}
OPTION& OPTION::operator+=(const OPTION& r) {
    return *this = *this + r;
}




NODE::NODE(OPTION* p, int n):p(n?new OPTION[n]:0), n(p?n:0) {
    if (this->p == 0 && n!=0)
        return;
    for (int x = 0; x < n; x++) this->p[x] = p[x];
}
NODE::NODE(int n):p(n?new OPTION[n]:0), n(p?n:0) {
    if (p == 0 && n!=0)
        return;
}
NODE::NODE(const NODE& n) : p(n.n ? new OPTION[n.n] :0), n(p ? n.n : 0) {
    if (p == 0 && n.n!=0)
        return;
    for (int x = 0; x<NODE::n; x++) p[x] = n.p[x];
}
NODE::NODE(NODE&& n)noexcept: p(n.p), n(n.n) {
    (OPTION*&)(n.p) = 0;
    (int&)n.n = 0;
}
NODE  NODE::operator*()const {
    int n = this->n;
    if (n == 0) return *this;
    OPTION* t = new OPTION[n];
    for (int x = 0; x < n; x++) t[x] = p[x];
    for (int x = 0; x < n - 1; x++)
        for (int y = x + 1; y < n; y++) {
            if (t[x]== t[y]) {
                for (int m = x + 1, n = y + 1; n < n - 1; n++, m++)
                    t[m] = t[n];
                n -= (y - x);
                y = x;
            }
        }
    NODE r(t, n);
    //try {
    //    if (t != nullptr)delete[]t;
    //    t = nullptr;
    //}
    //catch (...) {
    //    throw "initializing failed！";
    //}
    return r;
}
NODE NODE::operator+(const OPTION& n)const {
    NODE r(this->n + 1);
    for (int x = 0; x < this->n; x++) r.p[x] = *p[x];
    r.p[this->n] = n;
    return *r;
}
NODE NODE::operator+(const NODE& n)const {
    if (this->n == 0) return n;
    if (n.n == 0) return *this;
    NODE r(this->n + n.n);
    for (int x = 0; x < this->n; x++) r.p[x] = *p[x];
    for (int x = 0; x < n.n; x++) r.p[x+this->n] = *n.p[x];
    return *r;
}
NODE NODE::operator*(const NODE& n)const {
    if (this->n == 0) return *this;
    if (n.n == 0) return n;
    NODE r(this->n * n.n);
    int k = 0;
    for(int x=0; x< this->n; x++)
        for (int y = 0; y < n.n; y++) {
            if (p[x][p[x]-1].getend() != n.p[y][0].getbegin()) throw "Can not tansship from buses!";
            try {
                r.p[k] = p[x] + n.p[y];  //连接运算
            }
            catch (const char* e) {
                //const char* p = e;
            }
            k++;
        }
    return *r;
}
NODE& NODE::operator=(const NODE& n) {
    if(this == &n) return *this;
    if (p) delete[]p;
    (OPTION*&)p = new OPTION[n.n];
    (int&)(NODE::n) = p ? n.n : 0;
    for (int x= 0; x < n.n; x++) p[x] = n.p[x];
    return *this;
}
NODE& NODE::operator=(NODE&& n)noexcept {
    if (this == &n) return *this;
    if (p) delete[]p;
    (OPTION*&)p = n.p;
    (int&)(NODE::n) = n.n;
    (OPTION*&)(n.p) = nullptr;
    (int&)(n.n) = 0;
    return *this;
}
NODE& NODE::operator+=(const OPTION& n) {
    return *this = *this + n;
}
NODE& NODE::operator+=(const NODE & n)  {
    return *this = *this + n;
}
NODE& NODE::operator*=(const NODE& n) {
    return *this = *this * n;
}
OPTION& NODE::operator[](int x) {
    if (x < 0 || x >= n)
        throw"error";
    return p[x];
}
NODE::operator int&() {
    return n;
}
NODE::~NODE()noexcept {
    if (p) {
        delete[]p;
        (OPTION*&)p = 0;
        (int&)n = 0;
    }
}
void NODE::print()const {
    for (int m = 0; m < n; m++) {
        p[m].print();
    }
}



MAT::MAT(int r, int c) : p((r!=0&&c!=0)?new NODE [r * c]:0),  r(p ? r : 0), c(p? c : 0) {
    if (MAT::p == 0 && r != 0 && c != 0) return;
}
MAT::MAT(const MAT& a) : p((a.r!=0 && a.c!=0)?new NODE [a.r*a.c]:0), r(p? a.r:0), c(p ? a.c:0) {
    if (p == 0 && a.r != 0 && a.c != 0) return;
    for (int k = 0; k < r * c - 1; k++) p[k] = a.p[k];
}
MAT::MAT(MAT&& a)noexcept: p(a.p), r(a.r), c(a.c){
    (NODE*&)(a.p) = 0;
    (int&)(a.r) = (int&)(a.c) = 0;
}
MAT::~MAT() {
    if (p) {
        delete[] p;
        (NODE*&)p = 0;
        (int&)r = (int&)c = 0;
    }
}
int MAT::noaccess()const {
    for (int x = r * c - 1; x >= 0; x--) if (p[x].operator int &()==0) return 0;
    return 1;
}
int& MAT::operator()(int x, int y) {
    if (x < 0 || x >= r) throw"error";
    if (y < 0 || y >= c) throw"error";
    return p[x * c + y];
}
NODE* MAT::operator[](int r) {
    if (r < 0 || r >= MAT::r) throw"error";
    return p+r * c;
}
MAT& MAT::operator=(const MAT& a) {
    if (this == &a) return *this;
    if (p) delete[]p;
    (NODE*&)p = new NODE[a.r*a.c];
    (int&)r = a.r;
    (int&)c = a.c;
    for (int k = r * c - 1; k >= 0; k--)
        p[k] = a.p[k];
    return *this;
}
MAT& MAT::operator=(MAT&& a) {
    if (this == &a) return *this;
    if (p) delete[]p;
    (NODE*&)p = a.p;
    (int&)r = a.r;
    (int&)c = a.c;
    (NODE*&)(a.p) = 0;
    (int&)(a.r)=(int&)(a.c)=0;
    return *this;
}
MAT MAT::operator*(const MAT& a)const {
    if (c != a.r)
        throw"error";
    int t;
    MAT s(r, a.c);                 //每个节点皆为空线路
    for (int h = 0; h < r; h++)
        for (int j = a.c - 1; j >= 0; j--) {
            if (h == j) continue;
            t = h * s.c + j;
            for (int k = 0; k < c; k++)
                if (k != h && k!=j) //新增路线数
                    s.p[t]+= p[h * c + k] * a.p[k * a.c + j];
        }
    return s;
}
MAT MAT::operator+(const MAT& a)const {
    if (r!=a.r || c !=a.c )
       throw"error";
    MAT s(*this);
    for (int h = r * c - 1; h >= 0; h--)
        s.p[h] += a.p[h];
    return s;
}
MAT& MAT::operator+=(const MAT& a) {
    return *this = *this + a;
}
MAT& MAT::operator*=(const MAT& a) {
    return *this = *this * a;
}
MAT& MAT::operator()(int ro, int co, const OPTION& a) {
    p[ro * c + co] += a;
    return *this;
}
//根据起点站s和终点站t找到最少转乘次数noft的若干线路r,返回线路数
int MAT::miniTran(int s, int t, int& notf, OPTION(&r)[100])const {
    int u, v, w, x, y, z;//z:返回实际最少转乘线路数
    int b = 0, e = 0;       //包含起点s的起始线路数b(线路存放在bls),包含终点t的起始线路数e(线路存放在els)
    int nott[100]{};        //对应规划线路r的转乘次数
    int bls[20], els[20];   //bls:包含起点s的起始线路
    NODE rou;
    for (z = 0; z < TOTAL::cnt_line; z++) { //寻找包含起点或终点相关公交线路下标
        if (TOTAL::line[z].has(s) != -1)
            if (b < 20)
                bls[b++] = z;
        if (TOTAL::line[z].has(t) != -1)
            if (e < 20)
                els[e++] = z;
    }
    for (x = z = 0; x < b; x++)
        for (y = 0; y < e; y++) {
            rou = TOTAL::tra[bls[x]][els[y]]; //得到两线路的所有转乘线路
            w = TOTAL::tra(bls[x], els[y]);
            if (w == 0)
                continue;   //转乘线路数==0
            for (v = 0; v < w; v++) {
                u = rou[v];         //线路得到转乘次数
                if (z == 0 || u < nott[0]) {//若nott为空，或转乘次数比nott[0]小
                    nott[0] = u;
                    r[0] = rou[v];
                    z = 1;
                }
                if (u == nott[0]) { //和已有线路转乘次数相同时，则插入
                    if (z == 100) return z;
                    nott[z] = u;
                    r[z] = rou[v];
                    z++;
                }
            }
        }
    notf = nott[0]; //nott[0]到的nott[z-1]的转乘次数都相同
    return z;       //返回最少转乘线路数
}
void MAT::print()const {
    for(int x=0; x < r; x++)
        for (int y = 0; y < c; y++) {
            printf("Node(%d,%d) has %d routes:\n", x, y, (int)(p[x * c + y]));
            p[x * c + y].print();
        }

}


TOTAL::TOTAL() {
    obs++;
}
TOTAL::TOTAL(const char* flstop, const char* flline) {
    int  m, n, p, q, r, * s, * t;
    FILE* fs, * fl;
    fs = fopen(flstop, "r");
    fl = fopen(flline, "r");
    if (fs == 0 || fl == 0) throw "File open error!";
    fscanf(fs, "%d", &cnt_point);
    point = new POINT[cnt_point];
    for (m = 0; m < cnt_point; m++) {
        fscanf(fs, "%d%d", &point[m].getx(), &point[m].gety());
        point[m].getnum() = m + 1;      //公交线路编号从1开始
    }
    fclose(fs);
    fscanf(fl, "%d", &cnt_line);
    s = new int[cnt_line];            //每条线路的站点数
    t = new int[100];           //每条线路的站点数不超过100站
    for (m = 0; m < cnt_line; m++) {
        fscanf(fl, "%d", &s[m]);
    }
    *(LINE**)&line = new LINE[cnt_line];
    for (m = 0; m < cnt_line; m++) {
        for (n = 0; n < s[m]; n++) {
            fscanf(fl, "%d", &t[n]);
            t[n]--;
        }
        line[m] = LINE(m + 1, s[m], t);
    }
    fclose(fl);
    //判断是否有交点，没有交点就无法构建闭包矩阵
    for (m = 0; m < cnt_line; m++) {
        for (p = n = 0; n < cnt_line; n++)
            if (m != n) p += TOTAL::line[m].cross(TOTAL::line[n]);
        if (p == 0) {
            printf("line %d does nott cross any line\n", m + 1);
            throw  "there is independent line";
        }
    }
    MAT ra(cnt_line, cnt_line);
    OPTION a;
    CROSS* u = new CROSS[100];
    for (m = 0; m < cnt_line; m++)
        for (n = 0; n < cnt_line; n++)
        {
            if (m == n) {                    //某条线路内的各点可以两两相互到达
                u[0] = CROSS(m, n, -1);
                a = OPTION(&u[0],1 );
                ra(m, n, a);
                continue;
            }
            p = 0;                      //某两条线路的交点个数
            for (q = TOTAL::line[m].COUNT() - 1; q >= 0; q--) {
                r = TOTAL::line[m][q];
                if (TOTAL::line[n].has(r) != -1)   //两条线路有交点，可以通过一次换乘到达
                {
                    u[p] = CROSS(m, n, r);
                    a = OPTION(&u[p++],1); //线路只有一次转乘
                    ra(m, n, a);
                }
            }
        }
    tra = raw = ra;
    for (n = 2; n < cnt_line; n++) {//构造闭包矩阵
        raw *= ra;
        tra += raw;
    }
    raw = ra;
    delete s;
    delete t;
    delete[]u;
    obs++;
}
TOTAL::~TOTAL() {
    obs--;
    if (obs) return;
    if (point) {
        delete[]point;
        *(POINT**)&point = 0;
    }
    if (line) {
        delete[]line;
        *(LINE**)&line = 0;
    }
}
//根据步行起点和终点找到最少转乘次数n的若干线路r，返回线路数
int TOTAL::miniTran(int fx, int fy, int tx, int ty, int& f, int& t, int& n, OPTION(&r)[100]) {
    int m;
    double df, tf, dt, tt;
    f = 0;      //设离起点最近的站点f
    df = sqrt((point[0].getx() - fx) * (point[0].getx() - fx) + (point[0].gety() - fy) * (point[0].gety() - fy));
    t = 0;      //设离终点最近的站点t
    dt = sqrt((point[0].getx() - tx) * (point[0].getx() - tx) + (point[0].gety() - ty) * (point[0].gety() - ty));
    for (m = 1; m < TOTAL::cnt_point; m++) {         //搜索离起点或终点最近的站点
        tf = sqrt((point[m].getx() - fx) * (point[m].getx() - fx) + (point[m].gety() - fy) * (point[m].gety() - fy));
        if (df > tf) { df = tf;  f = m; }   //离步行起点最近的站点，存在f中
        tt = sqrt((point[m].getx() - tx) * (point[m].getx() - tx) + (point[m].gety() - ty) * (point[m].gety() - ty));
        if (dt > tt) { dt = tt;  t = m; }
    }
    if (f == t) return 0;   //起点和终点相同，不用乘车
    return TOTAL::tra.miniTran(f, t, n, r);
}
