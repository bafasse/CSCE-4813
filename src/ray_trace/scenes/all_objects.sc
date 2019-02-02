camera [
eye 0 0 10 
look 0 0 -1
up 0 1 0
angle 60
near-far 8 15
]

light [
position -3 0 3
color 0.5 0.5 0.5
function 1 0.2 0
]

light [
position 3 0 3
color 0.5 0.5 0.5
function 1 0.2 0
]

light [
position 0 -3 3
color 0.5 0.5 0.5
function 1 0.2 0
]

light [
position 0 3 3
color 0.5 0.5 0.5
function 1 0.2 0
]

mastersubgraph root [

trans [
translate 0 0 -2
translate 3 4 0
rotate 0 1 0 -20
rotate 0 0 1 90
object cylinder [
diffuse 0 1 1
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 3 2 0
rotate 0 1 0 -20
rotate 0 0 1 80
object cylinder [
diffuse 1 0 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 3 0 0
rotate 0 1 0 -20
rotate 0 0 1 70
object cylinder [
diffuse 0 1 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 3 -2 0
rotate 0 1 0 -20
rotate 0 0 1 60
object cylinder [
diffuse 0 0 1
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 3 -4 0
rotate 0 1 0 -20
rotate 0 0 1 50
object cylinder [
diffuse 1 1 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 1 4 0
rotate 0 1 0 -20
rotate 0 0 1 -90
object cone [
diffuse 0 1 1
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 1 2 0
rotate 0 1 0 -20
rotate 0 0 1 -80
object cone [
diffuse 1 0 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 1 0 0
rotate 0 1 0 -20
rotate 0 0 1 -70
object cone [
diffuse 0 1 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 1 -2 0
rotate 0 1 0 -20
rotate 0 0 1 -60
object cone [
diffuse 0 0 1
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate 1 -4 0
rotate 0 1 0 -20
rotate 0 0 1 -50
object cone [
diffuse 1 1 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -1 4 0
object cube [
diffuse 0 1 1
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -1 2 0
object cube [
diffuse 1 0 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -1 0 0
object cube [
diffuse 0 1 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -1 -2 0
object cube [
diffuse 0 0 1
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -1 -4 0
object cube [
diffuse 1 1 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -3 4 0
object sphere [
diffuse 0 1 1
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -3 2 0
object sphere [
diffuse 1 0 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -3 0 0
object sphere [
diffuse 0 1 0
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -3 -2 0
object sphere [
diffuse 0 0 1
specular 1 1 1      
shine 20
]
]

trans [
translate 0 0 -2
translate -3 -4 0
object sphere [
diffuse 1 1 0
specular 1 1 1      
shine 20
]
]

]

