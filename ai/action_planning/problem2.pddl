(define (problem m2)
  (:domain game)
  (:objects l1 l2 l3 l4 l5 l6 l7 l8 l9)

  (:init
    (playerisalive)
    (playerisin l1)
    (caveleadsto l1 l2)
    (caveleadsto l1 l5)
    (caveleadsto l2 l1)
    (caveleadsto l2 l3)
    (caveleadsto l3 l2)
    (caveleadsto l3 l4)
    (caveleadsto l4 l3)
    (caveleadsto l5 l7)
    (caveleadsto l5 l2)
    (caveleadsto l5 l9)
    (caveleadsto l5 l6)
    (caveleadsto l6 l5)
    (caveleadsto l6 l8)
    (caveleadsto l7 l4)
    (caveleadsto l8 l6)
    (cavehasmonster l3)
    (cavehastreasure l4)
    (cavehashole l7)
    (cavehasweapons l6)
    (cavehasshoes l8)
  )
  
  (:goal (and
    (playerisalive)
    (playerisin l1)
    (playerhastreasure l4)
  ))
)