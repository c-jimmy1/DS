
#include <list>
#include <math.h>
#include <set>
#include "image.h"
#include "priority_queue.h"

// Function to find the neighbors of a pixel and add them to the priority queue with a new distance value
void findNeighbors(const DistancePixel& p, Image<Color>& input, Image<DistancePixel>& distance_image,
  DistancePixel_PriorityQueue& pq, std::set<DistancePixel*>& visited) {
  int w = input.Width();
  int h = input.Height();
  
  // check all 8 neighboring pixels
  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      // check if the neighboring pixel is within the image bounds
      if (p.getX()+x >= 0 && p.getX()+x < w && p.getY()+y >= 0 && p.getY()+y < h) {
        // check if the neighboring pixel has been visited before by finding it in the set
        bool visit = false;
        if (visited.find(&distance_image.GetPixel(p.getX()+x, p.getY()+y)) != visited.end()) {
          visit = true;
        }
        // if the neighboring pixel has not been visited, update its distance value
        if (!visit) {
          // get the neighboring pixel's distance pixel object
          DistancePixel& neighbor = distance_image.GetPixel(p.getX()+x, p.getY()+y);
          neighbor.setX(p.getX()+x);
          neighbor.setY(p.getY()+y);
          // calculate the distance between the current pixel and the neighboring pixel
          double distance = sqrt(((p.getX()+x)-p.getX())*((p.getX()+x)-p.getX()) +
            ((p.getY()+y)-p.getY())*((p.getY()+y)-p.getY()));
          // update the distance value of the neighboring pixel if a shorter path is found
          if (neighbor.getValue() > distance + p.getValue()) {
            // add the pixel to the priority queue if it has not been added yet
            if (neighbor.getValue() == w*h){
              pq.push(&neighbor);
            }
            // update the distance value of the neighboring pixel
            neighbor.setValue(distance + p.getValue());
          }
        }
      }
    }
  }
}


// Function to find the maximum distance value in the distance image and return it as a double
// Uses the FindNeighbors function to find the neighbors of each pixel and update their distance values
// to produce the distance image with the correct colors.
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  
  //
  // IMPLEMENT THIS FUNCTION
  //
  // (using the advancing front method, and a priority queue)
  //

  // initialize variables for the width and height of the input image
  int w = input.Width();
  int h = input.Height();
  // initialize the maximum distance value to 0
  double max = 0;

  // create a vector to store the black pixels
  std::vector<DistancePixel*> black_pixels;
  // create a set to store the visited pixels
  std::set<DistancePixel*> visited;

  // loop over the pixels in the input image
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
      // grab the color of the current pixel
      const Color& c = input.GetPixel(i,j);

      // grab all of the black pixels and set their distance values to 0
      if (c.isBlack()){
        DistancePixel& p = distance_image.GetPixel(i,j);
        p.setX(i);
        p.setY(j);
        p.setValue(0);
        black_pixels.push_back(&p);
        visited.insert(&p);
      }
      // if the pixel is not black, set its distance value to the maximum possible value (w*h)
      else {
        DistancePixel& p = distance_image.GetPixel(i,j);
        p.setValue(w*h);
      }
    }
  }
    // create a priority queue starting with the black pixels
  DistancePixel_PriorityQueue pq(black_pixels);

  // loop over the priority queue until it is empty
  while (!pq.empty()){
    // grab the pixel with the smallest distance value (the top of the priority queue) and remove it
    const DistancePixel& p = *pq.top();
    pq.pop();
    // add the pixel to the visited set
    DistancePixel& p2 = distance_image.GetPixel(p.getX(), p.getY());
    p2.setX(p.getX());
    p2.setY(p.getY());
    p2.setValue(p.getValue());
    visited.insert(&p2);
    std::cout << "Pixel: " << p.getX() << ", " << p.getY() << " Value: " << p.getValue() << std::endl;
    // find the neighbors of the current pixel
    findNeighbors(p, input, distance_image, pq, visited);
  }
  
  // loop over the pixels in the distance image to find the maximum distance value
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){ 
      const DistancePixel& p = distance_image.GetPixel(i,j);
      if (p.getValue() > max){
        max = p.getValue();
      } 
    }
  }
  // return the maximum distance value
  std::cout << "Max: " << max << std::endl;
  return max;
}