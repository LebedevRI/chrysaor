(herbie-test ([mu 3.986004418e+14] [alt (<= 600000 default 42164136)]
              [Vx (<= 0 default 10000)] [Vy (<= -1000 default 1000)])
  "semi-major axis"
  (let* (
          [V (sqrt (+ (sqr Vx) (sqr Vy)))]
          [V2 (sqr V)]
          [sma (/ 1 (- (/ 2 alt) (/ V2 mu)))]
        )
    sma
  )
)
