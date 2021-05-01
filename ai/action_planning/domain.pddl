(define (domain game) 
  (:requirements
    :strips                 ; basic preconditions and effectss
    :negative-preconditions ; to use not in preconditions
  )
  (:predicates
    (playerisin      ?l)    
    (cavehashole     ?l)
    (cavehasmonster  ?l)      
    (cavehasweapons  ?l)
    (cavehastreasure ?l)
    (cavehasshoes    ?l)
    (caveleadsto ?l1 ?l2)
    (playerisalive)
    (playerhasshoes)
    (playerhasweapons)
    (playerhastreasure ?l) 
  )

  (:action goto_clean_cave
    :parameters (?from ?to)
    
    :precondition (and
      (playerisin ?from)
      (caveleadsto ?from ?to)
      (not (cavehasmonster ?to))
      (not (cavehashole    ?to))
      (not (cavehasweapons ?to))
      (not (cavehasshoes   ?to))
      (playerisalive)
    )
    
    :effect (and
      (playerisin ?to)
      (not (playerisin ?from))
    )
  )
  
  (:action goto_weapons_cave
    :parameters (?from ?to)
    
    :precondition (and
      (playerisin ?from)
      (caveleadsto ?from ?to)
      (cavehasweapons ?to)
      (playerisalive)
    )
    
    :effect (and
      (playerisin ?to)
      (not (playerisin ?from))
      (not (cavehasweapons ?to))
      (playerhasweapons)
    )
  )
  
  (:action goto_shoes_cave
    :parameters (?from ?to)
    
    :precondition (and
      (playerisin ?from)
      (caveleadsto ?from ?to)
      (cavehasshoes ?to)
      (playerisalive)
    )
    
    :effect (and
      (playerisin ?to)
      (not (playerisin ?from))
      (not (cavehasshoes ?to))
      (playerhasshoes)
    )
  )
  
  (:action goto_treasure_cave
    :parameters (?from ?to)
    
    :precondition (and
      (playerisin ?from)
      (caveleadsto ?from ?to)
      (cavehastreasure ?to)
      (playerisalive)
    )
    
    :effect (and
      (playerisin ?to)
      (not (playerisin ?from))
      (not (cavehastreasure ?to))
      (playerhastreasure ?to)
    )
  )
  
  (:action goto_monster_cave_unarmed
    :parameters (?from ?to)
    
    :precondition (and
      (playerisin ?from)
      (caveleadsto ?from ?to)
      (cavehasmonster ?to)
      (not (playerhasweapons))
      (playerisalive)
    )
    
    :effect (and
      (not (playerisalive))
    )
  )
  
  (:action goto_monster_cave_armed
    :parameters (?from ?to)
    
    :precondition (and
      (playerisin ?from)
      (caveleadsto ?from ?to)
      (cavehasmonster ?to)
      (playerhasweapons)
      (playerisalive)
    )
    
    :effect (and
      (playerisin ?to)
      (not (playerisin ?from))
      (not (playerhasweapons))
      (not (cavehasmonster ?to))
    )
  )
  
  (:action goto_hole_cave_barefoot
    :parameters (?from ?to)
    
    :precondition (and
      (playerisin ?from)
      (caveleadsto ?from ?to)
      (cavehashole ?to)
      (not (playerhasshoes))
      (playerisalive)
    )
    
    :effect (and
      (not (playerisalive))
    )
  )
  
  (:action goto_hole_cave_shoed
    :parameters (?from ?to)
    
    :precondition (and
      (playerisin ?from)
      (caveleadsto ?from ?to)
      (cavehashole ?to)
      (playerhasshoes)
      (playerisalive)
    )
    
    :effect (and
      (playerisin ?to)
      (not (playerisin ?from))
      (not (playerhasshoes))
    )
  )
)
