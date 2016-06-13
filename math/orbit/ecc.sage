Vx, Vy, alt, mu = var('Vx, Vy, alt, mu')

V = sqrt(Vx^2 + Vy^2)
V2 = V^2

sma = 1 / ((2 / alt) - (V2/mu))
soe = -mu/(2*sma)
srh = (vector([alt, 0, 0]).cross_product(vector([Vy, Vx, 0]))).norm()

srh = alt*vx # because

ecc = sqrt(1 + 2*soe*srh^2 / mu^2);

ecc
ecc.simplify()
ecc.simplify_full()
