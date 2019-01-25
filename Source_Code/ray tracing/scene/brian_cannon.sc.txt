camera [
  eye 1 1 1
  focus 0 0 0
  up 0 1 0
  angle 45
  near-far 0.05 5
]

light [
  position 1 1 1
  color 1 1 1
  function 0 0.4 0
]

light [
  position -1 1 1
  color 1 1 1
  function 0 0.4 0
]

light [
  position 1 1 -1
  color 1 1 1
  function 0 0.4 0
]

mastersubgraph ground [
	trans [
		scale 5.0 0.01 5.0
		object cube [
			diffuse 0.2 0.7 0.2
		]
	]
]

mastersubgraph cannonball [
	trans [
		scale 0.25 0.25 0.25
		object sphere [
			diffuse 0.01 0.01 0.01
			specular 0.1 0.1 0.1
			shine 10
		]
	]
]

mastersubgraph easy_barrel [
	trans [
		scale 0.6 0.2 0.2
		object cylinder [
			diffuse 0.1 0.1 0.1
		]
	]
]

mastersubgraph barrel_segment [
	trans [
		scale 0.6 0.01 0.01
		object cube [
			diffuse 0.05 0.05 0.05
			specular 0.1 0.1 0.1
			shine 10
		]
	]
]

mastersubgraph two_barrel_segments [
	trans [
		translate 0 0.1 0
		subgraph barrel_segment
	]
	trans [
		translate 0 -0.1 0
		subgraph barrel_segment
	]
]

mastersubgraph more_barrel_segments [
	trans [
		rotate 1 0 0 0
		subgraph two_barrel_segments
	]
	trans [
		rotate 1 0 0 5
		subgraph two_barrel_segments
	]
	trans [
		rotate 1 0 0 10
		subgraph two_barrel_segments
	]
]

mastersubgraph barrel [
	trans [
		rotate 1 0 0 0
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 15
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 30
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 45
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 60
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 75
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 90
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 105
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 120
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 135
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 150
		subgraph more_barrel_segments
	]
	trans [
		rotate 1 0 0 165
		subgraph more_barrel_segments
	]
]

mastersubgraph wheel_spoke [
	trans [
		scale 0.5 0.02 0.02
		object cube [
			diffuse 0.4 0.2 0.07
		]
	]
]

mastersubgraph wheel_spokes [
	trans [
		rotate 0 1 0 0
		subgraph wheel_spoke
	]
	trans [
		rotate 0 1 0 45
		subgraph wheel_spoke
	]
	trans [
		rotate 0 1 0 90
		subgraph wheel_spoke
	]
	trans [
		rotate 0 1 0 135
		subgraph wheel_spoke
	]
]

mastersubgraph easy_wheel [
	trans [
		scale 0.5 0.05 0.5
		object cylinder [
			diffuse 0.2 0.2 0.2
		]
	]
]

mastersubgraph wheel [
	trans [
		subgraph wheel_spokes
	]
	trans [
		scale 2.4 0.1 2.4
		rotate 0 0 1 90
		subgraph barrel
	]
]

mastersubgraph root [
	trans [
		subgraph ground
	]
	trans [
		translate 0.10 0.35 0
		rotate 0 0 1 30
		subgraph barrel
	]
	trans [
		translate 0 0.25 -0.13
		rotate 1 0 0 90
		subgraph wheel
	]
	trans [
		translate 0 0.25 0.13
		rotate 1 0 0 90
		subgraph wheel
	]
	trans [
		translate -0.3 0.2 0.40
		subgraph cannonball
	]
]