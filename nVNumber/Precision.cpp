#include "common.h"
#include <nV/Number.h>

namespace nV {
uint Precision(Kernel& k, const var& x) {
    if (x.isObject()) {
        if (x.object().type == $.Real)
            return x.cast<Real>().precision();
        return -1;
    }
    if (x.isTuple()) {
        uint n = -1;
        for (uint i = 0; i < x.tuple().size; ++i) {
            uint t = Precision(k, x.tuple()[i]);
            if (t < n)
                n = t;
        }
        return n;
    }
    return -1;
}
}

using namespace nV;

CAPI void CVALUE(System, Precision)(Kernel& k, var& r, Tuple& x) {
	if (x.size == 1)
		r = new Integer(Real::default_precision());
    else if (x.size == 2) {
        uint n = Precision(k, x[1]);
        if (n == -1)
            r = $.Infinity;
        else
            r = new Integer(n);
    }
}
