PrintTime[R_]:=Print[Part[R,1]]
R=Timing[GroebnerBasis[{x^10*y^10*z+x^10*y^3+y^10*z-9+z^10,z^2-8,x^5*z^8-9}]];
PrintTime[R]
R=Timing[GroebnerBasis[{x^10*y^10+x^10+y^10-9+z^10,y*z^2-8,x^5*z^8-9}]];
PrintTime[R]
R=Timing[GroebnerBasis[{100x^10*y^10*z^5+8x^10*y+5y^10*z-9+2z^10,7*y*z^2-8*x,12*x^5*z^8-9}]];
PrintTime[R]
(*R=Timing[GroebnerBasis[{x^10*y^10*p^2+x^10+y^10-9+z^10*p,y*z^2*p^5-8x,x^5*z^8-9p+8,14x*p+8*y*z^5-3}]];
PrintTime[R]*)
R=Timing[GroebnerBasis[{x^10*y^10*p+x^10+y^10-9+z^10,y*z^2-8,x^5*z^8-9p-8,3x*p-9}]];
PrintTime[R]
R=Timing[GroebnerBasis[{100*x^4*y^4*p^2+x^3*z^2+y^2*p-9+z^3,y*z^2-8,x^3*z^2-9p-8,3x*p^4-9}]];
PrintTime[R]
(*R=Timing[GroebnerBasis[{100*x^4*y^4*p^2+91*x^3*z^2+y^2*p-9+z^3,y*z^2*p^3-8,x^3*z^2*q^2-9p-8y,3x*p^4-9z-73,5*x^2*y*q-3p^3-77}]];
PrintTime[R]*)
(*R=Timing[GroebnerBasis[{100*x^4*y^4*p^2+x^3*z^2+y^2*p-9+z^3,y*z^2-8q-93,x^3*z^2-9p*q-8,3x*p^4-9,5x*y+9*q^2-89}]];
PrintTime[R]*)
R=Timing[GroebnerBasis[{x^2+y*q+z*q-9,y^2+z*q-8*p,x*y+p^2-20*q-99,p*q-x*z*q-2,p+q^2-y-30}]];
PrintTime[R]
R=Timing[GroebnerBasis[{x^2+y^2+z^2-1,x*y-z+2,z^2-2*x+3*y}]];
PrintTime[R]
R=Timing[GroebnerBasis[{x^2+y^2+z^2-1,x*y-z+2,z^2-2*x+3*y^2,x*q-y*z-5}]];
PrintTime[R]
R=Timing[GroebnerBasis[{x^5+y^4+z^3-1,x^3+y^3+z^2-1}]];
PrintTime[R]
