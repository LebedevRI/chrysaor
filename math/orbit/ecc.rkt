; sqrt(((alt^2)*(Vx^4) + (alt^2)*(Vx^2)*(Vy^2) - 2*alt*mu*(Vx^2) + (mu^2)) / (mu^2))
; formula=(lambda%20(alt%20Vx%20Vy%20mu)%20(sqrt%20(%2F%20(%2B%20(-%20(%2B%20(*%20(pow%20alt%202)%20(pow%20Vx%204))%20(*%20(*%20(pow%20alt%202)%20(pow%20Vx%202))%20(pow%20Vy%202)))%20(*%20(*%20(*%202%20alt)%20mu)%20(pow%20Vx%202)))%20(pow%20mu%202))%20(pow%20mu%202))))&formula-math=sqrt(((alt%5E2)*(Vx%5E4)%20%2B%20(alt%5E2)*(Vx%5E2)*(Vy%5E2)%20-%202*alt*mu*(Vx%5E2)%20%2B%20(mu%5E2))%20%2F%20(mu%5E2))
; (lambda (alt Vx Vy mu) (sqrt (/ (+ (- (+ (* (pow alt 2) (pow Vx 4)) (* (* (pow alt 2) (pow Vx 2)) (pow Vy 2))) (* (* (* 2 alt) mu) (pow Vx 2))) (pow mu 2)) (pow mu 2))))&formula-math=sqrt(((alt^2)*(Vx^4) + (alt^2)*(Vx^2)*(Vy^2) - 2*alt*mu*(Vx^2) + (mu^2)) / (mu^2))
(herbie-test ([mu 3.5316000e+12] [alt (<= 600000 default 40000000 )]
              [Vx (<= 0 default)] [Vy (<= 0 default)])
  "orbital eccentricity"
  (sqrt (/ (+ (- (+ (* (pow alt 2) (pow Vx 4)) (* (* (pow alt 2) (pow Vx 2)) (pow Vy 2))) (* (* (* 2 alt) mu) (pow Vx 2))) (pow mu 2)) (pow mu 2)))
)
