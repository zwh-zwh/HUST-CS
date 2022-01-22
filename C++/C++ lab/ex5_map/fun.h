#ifndef FUN_H
#define FUN_H
#pragma once
class POINT {        //公交站点
    int num;       //编号
    int x, y;       //坐标
public:
    POINT(int n=0, int x=0, int y=0);
    int& getx();
    int& gety();
    int& getnum();
};
class LINE{        //公交线路
    int num; //编号
    int* stop; //所有站点编号
    int count; //站点数量
public:
    LINE(int num = 0, int count = 0, int* stop = 0);
    LINE(const LINE& r);
    LINE(LINE&& r) noexcept;
    LINE& operator=(const LINE& r);
    LINE& operator=(LINE&& r)noexcept;
    virtual int has(int s)const;   //线路是否包含站点编号s,返回线路中的站次序号：-1表示没有
    virtual int cross(const LINE& b)const;  //两条公交线路相交则返回1
    virtual operator int ()const;  //取公交线路编号
    virtual int COUNT()const;       //取公交线路的站点数量
    virtual int& operator[](int x);//取线路某个站次的站点编号
    virtual ~LINE()noexcept;
};
class CROSS {        //从线路from经站点编号stop转至线路to
    int begin;       //现在乘坐的公交线路
    int end;         //需要转乘的公交线路
    int stop;       //站点编号
public:
    CROSS(int begin=0, int end=0, int stop=0);
    int operator==(const CROSS& t)const;
    virtual int& getbegin();//现在乘坐的公交线路
    virtual int& getend();//需要转乘的公交线路
    virtual int& getpoint();//转乘点的站点编号
};

class OPTION{       //一个转乘路径
    CROSS*const cross;//转乘路径上的所有转乘站点
    const int count; //转乘路径上转乘站点个数
public:
    OPTION(CROSS* tran = 0, int noft = 0);
    OPTION(const CROSS& t);
    OPTION(const OPTION& r);
    OPTION(OPTION&& r) noexcept;
    virtual int print()const;
    virtual operator int()const;        //得到转乘次数
    virtual int operator==(const OPTION& r)const;
    virtual OPTION operator *()const;    //去重复公交转乘
    virtual CROSS& operator[](int);      //取转乘
    virtual OPTION operator+(const OPTION& r)const;
    virtual OPTION& operator=(const OPTION& r);
    virtual OPTION& operator=(OPTION&& r) noexcept;
    virtual OPTION& operator+=(const OPTION& r);
    virtual ~OPTION() noexcept;
};

class NODE {        //转乘次数和线路
    OPTION* const p; //转乘路径方案
    int n;          //转乘路径方案数
public:
    NODE(OPTION*p, int n);
    NODE(int n = 0);
    NODE(const NODE &n);
    NODE(NODE&& n)noexcept;
    virtual NODE  operator*()const; //去掉相同转乘路径
    virtual NODE  operator+(const OPTION& n)const;  //添加一条路径
    virtual NODE  operator+(const NODE& n)const;    //添加多条路径
    virtual NODE  operator*(const NODE& n)const;
    virtual NODE& operator=(const NODE& n);
    virtual NODE& operator+=(const NODE& n);
    virtual NODE& operator+=(const OPTION& n);
    virtual NODE& operator*=(const NODE& n);
    virtual NODE& operator=(NODE&& n)noexcept;
    virtual OPTION& operator [](int x);
    virtual operator int&();        //可转乘路径数n
    virtual ~NODE()noexcept;
    virtual void print()const;      //打印转乘矩阵的元素
};

class MAT {
    NODE *const p;  //矩阵指针
    const int r, c; //矩阵的行数和列数
public:
    MAT(int r=0,int c=0);
    MAT(const MAT& a);
    MAT(MAT&& a)noexcept;
    virtual ~MAT();
    virtual int noaccess()const;                 //若有不可达站点则返回0
    virtual int miniTran(int b, int e, int& noft, OPTION(&r)[100])const;   //起点站次b,终点站次e,r最多存10条路径，返回路径数
    virtual NODE* operator[](int r);            //得到存储多种路径的NODE类元素的某行首址
    virtual int& operator()(int r, int c);      //得到r到c可转乘路径数目
    virtual MAT operator*(const MAT& a)const; //闭包运算：乘法
    virtual MAT operator+(const MAT& a)const; //闭包运算：加法
    virtual MAT& operator=(const MAT& a);
    virtual MAT& operator=(MAT&& a);
    virtual MAT& operator+=(const MAT& a);
    virtual MAT& operator*=(const MAT& a);
    virtual MAT& operator()(int r, int c, const OPTION& a);//将路径加入到r行c列元素中
    virtual void print()const;                  //打印转乘矩阵
};

class TOTAL {
public:
    static POINT*  point;       //所有公交站点
    static LINE*  line;       //所有公交线路
    static int  cnt_point, cnt_line;     //公交站数，公交线路数
    static MAT raw, tra;   //原始转乘矩阵， 闭包转乘矩阵
    static int  obs;        //对象数量
    TOTAL();
    TOTAL(const char* flstop, const char* flline);
    int miniTran(int fx, int fy, int tx, int ty, int& f, int& t, int& n, OPTION(&r)[100]);
    ~TOTAL();
};
extern TOTAL* total;


#endif // FUN_H
