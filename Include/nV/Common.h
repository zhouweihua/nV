#pragma once
#include "Object.h"
#include "Enum.h"
#include <gmp.h>
#ifdef _MSC_VER
#pragma comment(lib,"gmp")
// #pragma comment(lib,"mpir")
#endif
API extern void (*__gmp_free_func)(void*, size_t);

namespace nV {
inline sym primary(const var& x) {
    return $.PrimaryName[x.primary() + 1];
}
inline sym boolean(bool x) {
    return x ? $.True : $.False;
}
inline sym kind(const Key& x) {
    switch (x.kind()) {
    case  Key::String:
        return $.String;
    case Key::Integer:
        return $.Integer;
    }
    return $.Null;
}
inline Tuple* list(uint size, sym h = $.List) {
    Tuple* r = tuple(size + 1);
    r->tuple[0] = h;
    return r;
}
inline Tuple* list(const var& a, sym h = $.List) {
    Tuple* r = tuple(2);
    r->tuple[0] = h;
    r->tuple[1] = a;
    return r;
}
inline Tuple* list(const var& a, const var& b, sym h = $.List) {
    Tuple* r = tuple(3);
    r->tuple[0] = h;
    r->tuple[1] = a;
    r->tuple[2] = b;
    return r;
}
inline Tuple* list(const var& a, const var& b, const var& c, sym h = $.List) {
    Tuple* r = tuple(4);
    r->tuple[0] = h;
    r->tuple[1] = a;
    r->tuple[2] = b;
    r->tuple[3] = c;
    return r;
}
inline Tuple* list(const var& a, const var& b, const var& c, const var& d, sym h = $.List) {
    Tuple* r = tuple(5);
    r->tuple[0] = h;
    r->tuple[1] = a;
    r->tuple[2] = b;
    r->tuple[3] = c;
    r->tuple[4] = d;
    return r;
}
template <class Iter>
inline Tuple* list(uint size, Iter begin, sym h = $.List) {
    Tuple* r = tuple(size + 1);
    r->tuple[0] = h;
    for (uint i = 0; i < size; ++i, ++begin)
        r->tuple[i + 1] = *begin;
    return r;
}
template <class Iter>
inline Tuple* list(uint size, Iter begin, const var& h) {
    Tuple* r = tuple(size + 1);
    r->tuple[0] = h;
    for (uint i = 0; i < size; ++i, ++begin)
        r->tuple[i + 1] = *begin;
    return r;
}
template <class Func>
inline void map(Func f, Tuple& x) {
    for (uint i = 1; i < x.size; ++i)
        x[i] = f(x[i]);
}
API bool isCertain(const Tuple&);
inline bool isCertain(const var& x) {
    if (x.isTuple())
        return isCertain(x.tuple());
    return true;
}
inline bool isNumber(const Object& x) {
	return x.type == $.Integer
		|| x.type == $.Rational
		|| x.type == $.Real
		|| x.type == $.Complex
		|| x.type == $.RealI
		;
}
inline bool isNumber(const var& x) {
    return x.isObject() && isNumber(x.object());
}
inline bool lessPrimary(const var& x, const var& y) {
    return x.primary() < y.primary();
}
struct Pos {
    Pos* prev;
    const var* ptr;
    const var* end;
    Pos(const Tuple& x, Pos* y) : ptr(x.tuple), end(x.tuple + x.size), prev(y) {}
    Pos(const var& x, Pos* y) : ptr(&x), end((&x) + 1), prev(y) {}
    uint size() const {
        return end - ptr;
    }
    bool empty() const {
        return size() == 0;
    }
    const var& operator*() const {
        return *ptr;
    }
    const var* operator->() const {
        return ptr;
    }
    Pos& operator++() {
        ++ptr;
        return *this;
    }
    Pos& operator+=(uint n) {
        ptr += n;
        return *this;
    }
    Pos& operator--() {
        --ptr;
        return *this;
    }
    Pos& operator-=(uint n) {
        ptr -= n;
        return *this;
    }
};

API size_t mpz_hash(mpz_srcptr);
class Integer : public Object {
public:
    mpz_t mpz;
    virtual ~Integer() {
        mpz_clear(mpz);
    }
    virtual Integer* clone() const {
        Integer* r = new Integer();
        mpz_set(r->mpz, mpz);
        return r;
    }
    virtual int compare(const Object& x) const {
        return mpz_cmp(mpz, x.cast<Integer>().mpz);
    }
    virtual size_t hash() const {
        return mpz_hash(mpz);
    }
    API virtual void print(wostream&) const;
    Integer() : Object($.Integer) {
        mpz_init(mpz);
    }
    Integer(uint x) : Object($.Integer) {
        mpz_init_set_ui(mpz, x);
    }
    Integer(sint x) : Object($.Integer) {
        mpz_init_set_si(mpz, x);
    }
    Integer(double x) : Object($.Integer) {
        mpz_init_set_d(mpz, x);
    }
    Integer(const char* x, int y) : Object($.Integer) {
        mpz_init_set_str(mpz, x, y);
    }
    uint toUI() const {
        return mpz_get_ui(mpz);
    }
    sint toSI() const {
        return mpz_get_si(mpz);
    }
    double toD() const {
        return mpz_get_d(mpz);
    }
};
inline Integer& Z(const var& x) {
	return x.cast<Integer>();
}
inline Integer& Z(const Object& x) {
	return x.cast<Integer>();
}

API size_t mpq_hash(mpq_srcptr);
class Rational : public Object {
public:
    mpq_t mpq;
    virtual ~Rational() {
        mpq_clear(mpq);
    }
    virtual Rational* clone() const {
        Rational* r = new Rational();
        mpq_set(r->mpq, mpq);
        return r;
    }
    virtual int compare(const Object& x) const {
        return mpq_cmp(mpq, x.cast<Rational>().mpq);
    }
    virtual size_t hash() const {
        return mpq_hash(mpq);
    }
    API virtual void print(wostream&) const;
    Rational() : Object($.Rational) {
        mpq_init(mpq);
    }
    Rational(uint x, uint y) : Object($.Rational) {
        mpq_init(mpq);
        mpq_set_ui(mpq, x, y);
    }
    Rational(sint x, uint y) : Object($.Rational) {
        mpq_init(mpq);
        mpq_set_si(mpq, x, y);
    }
    Rational(double x) : Object($.Rational) {
        mpq_init(mpq);
        mpq_set_d(mpq, x);
    }
    Rational(const char* x, int y) : Object($.Rational) {
        mpq_init(mpq);
        mpq_set_str(mpq, x, y);
    }
    double toD() const {
        return mpq_get_d(mpq);
    }
};
inline Rational& Q(const var& x) {
	return x.cast<Rational>();
}
inline Rational& Q(const Object& x) {
	return x.cast<Rational>();
}

#define LOG_2_10 3.3219280948873623478703194294894
#define LOG_10_2 0.3010299956639811952137388947245
API size_t mpf_hash(mpf_srcptr);
class Real : public Object {
	uint prec;
public:
    mpf_t mpf;
    virtual ~Real() {
        mpf_clear(mpf);
    }
    virtual Real* clone() const {
        Real* r = new Real(precision());
        mpf_set(r->mpf, mpf);
        return r;
    }
    virtual int compare(const Object& x) const {
        return mpf_cmp(mpf, x.cast<Real>().mpf);
    }
    virtual size_t hash() const {
        return mpf_hash(mpf);
    }
    API virtual void print(wostream&) const;
    Real(uint n = 0) : Object($.Real), prec(std::max(static_cast<uint>(LOG_2_10 * n + 0.5), mpf_get_default_prec())) {
        mpf_init2(mpf, prec);
    }
    Real(uint x, uint n) : Object($.Real), prec(std::max(static_cast<uint>(LOG_2_10 * n + 0.5), mpf_get_default_prec())) {
        mpf_init2(mpf, prec);
        mpf_set_ui(mpf, x);
    }
    Real(sint x, uint n) : Object($.Real), prec(std::max(static_cast<uint>(LOG_2_10 * n + 0.5), mpf_get_default_prec())) {
        mpf_init2(mpf, prec);
        mpf_set_si(mpf, x);
    }
    Real(double x, uint n) : Object($.Real), prec(std::max(static_cast<uint>(LOG_2_10 * n + 0.5), mpf_get_default_prec())) {
        mpf_init2(mpf, prec),
        mpf_set_d(mpf, x);
    }
    Real(const char* x, int y, uint n) : Object($.Real), prec(std::max(static_cast<uint>(LOG_2_10 * n + 0.5), mpf_get_default_prec())) {
        mpf_init2(mpf, prec);
        mpf_set_str(mpf, x, y);
    }
	uint precision() const {
		return static_cast<uint>(LOG_10_2 * prec + 0.5);
	}
	static uint default_precision() {
		return static_cast<uint>(LOG_10_2 * mpf_get_default_prec() + 0.5);
	}
    uint toUI() const {
		return mpf_get_ui(mpf);
	}
    sint toSI() const {
		return mpf_get_si(mpf);
	}
    double toD() const {
		return mpf_get_d(mpf);
	}
};
inline Real& R(const var& x) {
	return x.cast<Real>();
}
inline Real& R(const Object& x) {
	return x.cast<Real>();
}
API extern double NaN;
inline bool isNaN(double x) {
	return x != x;
}
inline double toD(const Object& x) {
    if (x.type == $.Integer)
        return x.cast<Integer>().toD();
    if (x.type == $.Rational)
        return x.cast<Rational>().toD();
    if (x.type == $.Real)
        return x.cast<Real>().toD();
    return NaN;
}
inline int cmpD(const Object& x, double a, double b = 1.0) {
    if (x.type == $.Integer)
        return mpz_cmp_si(x.cast<Integer>().mpz,
                          static_cast<long>(a / b));
    if (x.type == $.Rational)
        return mpq_cmp_si(x.cast<Rational>().mpq, static_cast<long>(a),
                          static_cast<long>(b));
    if (x.type == $.Real)
        return mpf_cmp_d(x.cast<Real>().mpf, a / b);
    return ~0;
}
inline bool operator>(const Object& x, double y) {
    return cmpD(x, y) > 0;
}
inline bool operator<=(const Object& x, double y) {
    return !(x > y);
}
inline bool operator<(const Object& x, double y) {
    return cmpD(x, y) < 0;
}
inline bool operator>=(const Object& x, double y) {
    return !(x < y);
}
inline bool operator==(const Object& x, double y) {
    return cmpD(x, y) == 0;
}
inline bool operator!=(const Object& x, double y) {
    return !(x == y);
}

class String : public Object {
public:
    wstring str;
    virtual String* clone() const {
        return new String(str);
    }
    virtual int compare(const Object& x) const {
        return str.compare(static_cast<const String&>(x).str);
    }
    virtual size_t hash() const {
        return boost::hash<wstring>()(str);
    }
    API virtual void print(wostream&) const;
    String() : Object($.String) {}
    String(wcs x) : Object($.String) {
        str.assign(x);
    }
    String(const wstring& x) : Object($.String) {
        str.assign(x);
    }
    wcs toS() const {
        return str.c_str();
    }
};
inline String& S(const var& x) {
	return x.cast<String>();
}
inline String& S(const Object& x) {
	return x.cast<String>();
}

class Tag : public Object {
public:
    explicit Tag(sym $type, const var& $data) : Object($type), data($data) {}
    var data;
};
}
