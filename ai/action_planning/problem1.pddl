
(define (problem m1)
  (:domain game)
  (:objects l1 l2 l3 l4 l5 l6)

  (:init
    (playerisalive)
    (playerisin l1)
    (caveleadsto l1 l2)
    (caveleadsto l2 l1)
    (caveleadsto l2 l3)
    (caveleadsto l3 l2)
    (caveleadsto l3 l4)
    (caveleadsto l4 l3)
    (caveleadsto l1 l6)
    (caveleadsto l6 l4)
    (caveleadsto l1 l5)
    (caveleadsto l5 l4)
    (cavehasmonster l6)
    (cavehashole l5)
    (cavehastreasure l4)
  )
  
  (:goal (and
    (playerisin l1)
    (playerhastreasure l4)
  ))
)
