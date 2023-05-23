#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <list>
#include <math.h>
#include <set>
#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
        for (int j2 = 0; j2 < h; j2++) {
          const Color& c = input.GetPixel(i2,j2);      
          // skip all pixels that are not black
          if (!c.isBlack()) continue;
          // calculate the distance between the two pixels
          double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
          // store the closest distance to a black pixel
          if (closest < 0 || distance < closest) {
            closest = distance;
          }
        }
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

  //
  // IMPLEMENT THIS FUNCTION
  //
  // a small improvement on the NaiveDistanceFieldMethod
  //

  std::list <std::pair<int,int > > all_black;
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      const Color& c = input.GetPixel(i,j);
      if (c.isBlack()) {
        // add all the black pixels into the list with it's coordinates
        all_black.push_front(std::make_pair(i,j));
      }
    }
  }

  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      std::list<std::pair<int,int > >::iterator it;
      // iterator through every black coordinate and calculate the distance
      for (it = all_black.begin(); it != all_black.end(); ++it) {
        std::pair <int,int> coords = *it;
        // calculate the distance between the two pixels
        double distance = sqrt((i-coords.first)*(i-coords.first) + (j-coords.second)*(j-coords.second));
        // store the closest distance to a black pixel
        if (closest < 0 || distance < closest) {
          closest = distance;
        }
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  
  // Getting all the black pixels into one vector  
  std::vector <DistancePixel* > all_black;
  int w = input.Width();
  int h = input.Height();

  // Looping through all the pixels
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      const Color& c = input.GetPixel(i,j);
      DistancePixel& pixel = distance_image.GetPixel(i,j);
      pixel.setX(i);
      pixel.setY(j);
      // If there is a black pixel add it to the vector and set it's distance value to 0
      if (c.isBlack()) {
        all_black.push_back(&pixel);
        pixel.setValue(0);
      }
      // Otherwise, set it to the maximum possible double value
      else {
        pixel.setValue(std::numeric_limits<double>::max());
      }
    }
  }

  // Add all the black pixels to the priority queue
  DistancePixel_PriorityQueue priority(all_black);

  // Initializing a set that is used later to check if a pixel was already added to the priority queue before
  std::set <DistancePixel* > setPixel;
  double answer = 0.0;

  // While the priority queue is not empty
  while (!priority.empty()){
    // Get the top pixel of the priority queue and pop it from the queue
    const DistancePixel& priority_pixel = *priority.top();
    priority.pop();
    int xcoord = priority_pixel.getX();
    int ycoord = priority_pixel.getY();
    
    // Loop through the neighbors of the current pixel
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        
        // Check if the neighbor is in the bounds of the grid
        if (i + xcoord >= 0 && j + ycoord >= 0 && i + xcoord < w && j + ycoord < h) {
          // Calculate the distance and then create a neighbor pixel with it's new distance
          double distance = sqrt(((xcoord+i) - xcoord)*((xcoord+i) - xcoord) + ((ycoord+j) - ycoord)*((ycoord+j) - ycoord));
          DistancePixel& neighbor = distance_image.GetPixel(xcoord+i, ycoord+j);
          neighbor.setX(xcoord + i);
          neighbor.setY(ycoord + j);
          double new_distance = distance + priority_pixel.getValue();
          
          // If the new distance is closer than the old distance set the neighbor to that new distance
          if (new_distance < neighbor.getValue()) {
            neighbor.setValue(new_distance);
            
            // If the pixel was never in the priority queue, add it to the queue
            if (setPixel.find(&neighbor) == setPixel.end()) {
              priority.push(&neighbor);
              setPixel.insert(&neighbor);
            }
            // To find what the maximum distance is for the return statement
            if (new_distance > answer) {
              answer = new_distance;
            }
          }
        }
      }
    }
  }
  return answer;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================
