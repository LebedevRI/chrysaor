(herbie-test ([R1 (<= 600000 default 42164136.6)]
              [R2 (<= 600000 default 42164136.6)])
  "eccentricity from 2 apsises"
  (let* (
          [ecc (/ (- R1 R2) (+ R1 R2))]
        )
    ecc
  )
)
