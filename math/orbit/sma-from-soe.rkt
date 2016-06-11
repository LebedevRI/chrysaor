(herbie-test ([mu 3.986004418e+14] [soe (<= -1e8 default -1e6)])
  "semi-major axis from specific orbital energy"
  (let* (
          [sma (/ (- 0 mu) (* 2 soe))]
        )
    sma
  )
)
