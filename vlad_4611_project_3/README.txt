Vladimir Kuksenko
Kukse004




C range
rectangle drawn with correct indices
getPos() and getNorm() generate correct rectangular positions and normals
indicies work for any number of stacks or slices

B range
unset texture after drawing globe
getPos sets earthquakes in the correct locations (ring of fire is highly active)
draw::sphere used. (The magnitude of the earthquake is used to determine the size of the sphere drawn for the earthquakes)


A range
isSpherical == 1 on start
getPos and getNorm have correct spherical results
increased slices hides the warping on corners
earthquakes appear in correct spots
S key bound to transition between spherical and rectangular states
Smooth transitions using Lerp between rect and sphere Positions and Normals

