# C-Ray-Tracer
C++ Ray Tracing Algorithm (with threading)

Seth Balodi
C++ Ray Tracer Algorithm


![My image](https://user-images.githubusercontent.com/7054302/27884598-e1fa3128-61a2-11e7-86bf-3d5af0cd1662.png)
![My image](https://user-images.githubusercontent.com/7054302/27884601-e35866c0-61a2-11e7-9396-1345740649c1.png)
![My image](https://user-images.githubusercontent.com/7054302/27884604-e5a989ae-61a2-11e7-8f0c-5dd03a603f47.png)
![My image](https://user-images.githubusercontent.com/7054302/27884608-e7e666b0-61a2-11e7-9b30-7b6c81e49626.png)
![My image](https://user-images.githubusercontent.com/7054302/27884611-e98e49ec-61a2-11e7-9b02-8caf19c5a182.png)
![My image](https://user-images.githubusercontent.com/7054302/27884620-ebb072e0-61a2-11e7-91c2-4e4809c0be63.png)
![My image](https://user-images.githubusercontent.com/7054302/27884625-ee69c66c-61a2-11e7-8f13-37dcc9e1aa36.png)



For this assignment, we had to implement modules that would allow for parsing
of a JSON file into data structures which would then be used to set up a Ray
Tracing algorithm which would eventually use the QT framework to output a PNG file
that would contain the final result.

From looking at the project specification, I began first by understanding the
actual mathematics of a Ray Tracer. This will become important later on, as I 
will define certain objects and procedures that must be apparent in order for a 
Ray to be shot from a focus point (where the camera resides) and into a scene 
which will contain objects. 

The types of Objects were Spheres and Planes. I created an virtual class called
MotherOfObjects which would be the base class to the Sphere and Plane class. 
In the MotherOfObjects class, I created some methods, normal getters and setters 
in case I needed them, and also a pure virtual function, intersect. The intersect
function is very important as it is the backbone to the success of this algorithm.

The pure virtual function now needed to be implemented into both of my Object 
classes, and each intersect function was different due to the mathematics regarding
Spheres and Planes. 

The values for the Sphere and Plane were located in several JSON files which were
provided with the project. The JSON files also identified a Camera object, of which
there would be one, and Lights, of which there could be many. The Lights, along 
with the Spheres and Planes, could have multiple instances, so after I created
a Lights class which had all the member variables necessary by the constraints of 
the JSON file, I created two vectors. These vectors would be used to contain 
objets that could have multiple instances. I created a vector for Lights, called
vecLights and a vector for Objects (spheres and planes) called vecObjects. These
both held pointers of Lights* and MotherOfObjects* respectively. 

I then used QT, and in particular QVariantMaps, to parse the information from the 
JSON file and store it into my objects and furthermore into my vectors. Now I had
all the information to populate the scene as I needed. 

Going back to the mathematics behind ray tracing, I knew I needed a function to 
create a Primary Ray, which would have an Origin and a Direction. I knew I would 
also need a Shadow Ray after the intersection. I created a struct for Rays. I also
knew that I would be needing Coordinates for positioning of information from the 
JSON file. I created a Coordinate struct, which I used for the various positions
of "normal" and "center", etc. I created a Color struct to hold the color values 
(as they could only be ints, and the Coordinate struct housed doubles). 

I knew that I would be doing a lot of operations on the Coordinates, and slightly
on the colors, so I added operator overloads to ensure that I would be able to
do my own arithmetic on the Coordinates and vectors. Inside of my Coordinate struct
I added a function to compute the dot product of two vectors, which is essential
in observing the intersection of a sphere. After parsing, I decided to make a 
function that would calculate the values I needed for the Primary Ray. In this
function, I put in the point where the ray would be output, which would be the 
focus of the camera multiplied by the camera normal vector. I then subtracted this
value from the canera center to obtain the first point. The second point was tied
to the resolution of the camera and I performed a simple operation with the 
help that the professor and fellow students put on Piazza. The direction variable
throughout the program needed to be normalized, so I went back to my structs and 
created a normalize function for my vectors. 

After getting the origin and destination of the Primary Ray, I called the function 
and created the Ray that would be shot out at every pixel value (given by the height
and the width). Due to the properties of the Primary Ray and the sphere, there could
be multiple points where it intersects, but I only needed the nearest one, so I 
created a quick double variable that would store this and then itereated through
all of the pixels, and then all of hte objects to see if there was any intersection.
If there is an intersection, then a Shadow Ray (another ray created) would have 
to be shot from the point of intersection towards the light sources (which are 
all still contained in the vecLights vector). Calculating the point of intersection
using the nearest value was done using the Parametric Equation of a sphere. 
I took primary ray origin and subtracted from it the primary ray direction vector
multiplied by the nearest value of intersection. This outputs a coordinate which 
could be passed into my shadow ray function. This is because the shadow ray has
to begin at the point of intersection and go towards the lightVec objects. 

It is in this function where I calculate the pixel values. This is all dependent
on if the shadow ray hits an object or not. if it hits an object, then the resulting
pixel value at the particular pixel index should be (0,0,0) with an RBG interface.
This translates to black, which makes sense as the thing being intersected is being
blocked by another object. I do this by for looping through my vector of objects and
seeing if anythign intersects again. If it does, then the pixel is set to black.
If, however, the Shadow Ray goes to the light, a formula provided by the professor
in psueudocode calculates the values of the pixels using additional information 
provided by the JSON file, such as the lambert value. This allows for the color of 
the object to show through using the light. It shoudl be noted that the maximum
light value is the one we are interested in, so I have some code that loops through
the light vector and decides which light has the highest intensity. If the scale,
provided by the professor's pseudocode, is greater than 0, then the pixel is colored
based on the pixel_color equation provided. 

The rendering of the image into a PNG file is done using QT. For this part, I left
this function in my main function, called vtray.cpp. In this function, I use 
the height and width and pass them into a QImage object which I call imager. 
The format is set to QImage::Format_RGB32 based on the QT documentation. 
I then loop through all of the pixels, which I stored in a pixelsVector from 
the previous function, and I use the QRgb object to create an rgb value which is 
then parsed in to the setPixel command of the QImage object. What results is 
an image based on the algorithm stated above!

Those were my design and implementation decisions for the project!
