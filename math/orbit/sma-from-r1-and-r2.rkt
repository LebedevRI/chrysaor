(herbie-test ([R (<= 600000 default 6378136.6)]
              [r1 (<= 0 default 3.5786e+07)]
              [r2 (<= 0 default 3.5786e+07)])
  "semi-major axis from 2 apsises"
  (let* (
          [R1 (+ r1 R)]
          [R2 (+ r2 R)]
          [sma (/ (+ R1 R2) 2)]
        )
    sma
  )
)
