Vx, Vy, alt, mu = var('Vx, Vy, alt, mu')

V = sqrt(Vx^2 + Vy^2)
V2 = V^2

sma = 1 / ((2 / alt) - (V2/mu))
soe = -mu/(2*sma)
srh = (vector([alt, 0, 0]).cross_product(vector([Vy, Vx, 0]))).norm()

srh
srh.simplify()
srh.simplify_full()
