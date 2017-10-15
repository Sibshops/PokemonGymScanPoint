#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <limits>

///
struct Gym
{
  std::string Name_;
  double x_;
  double y_;
};

typedef std::vector<Gym> GymList;

const GymList kGymList =
  {
    {"LBC Welcome Sign", 40.587812,-79.746559},
    {"St Margaret Mary's Church", 40.587743,-79.718091},
    {"American Legion Armed Service Memorial",40.582353,-79.71109,},
    {"US Army Navy Memorial", 40.578705,-79.711798},
    {"Joshua Gibson Memorial", 40.574404,-79.744325},
    {"Joy Bear", 40.574605,-79.747242},
    {"USAF TR-513", 40.5748, -79.748528},
    {"Fort Crawford",40.554103,-79.760553},
    {"New Kensington Post Office",40.556364,-79.759869},
    {"Parnassus Park",40.559472,-79.760429},
    {"United Presbyterian Church",40.561412,-79.764283},
    {"Mt St Peter Church",40.563847,-79.761412},
    {"The River Community Church",40.564615,-79.760643},
    {"Daughters Of The American Revolution Park",40.568042,-79.75235},
    {"St Joseph Parish Center",40.569065,-79.763378},
    {"Not in My Hood Sign",40.569514,-79.767194},
    {"St. Paul Church",40.572881,-79.755897},
    {"Bethlehem Temple Faith Church",40.572593,-79.76795},
    {"St. Vladimirs Catholic Church",40.574697,-79.764821},
    {"Holy Virgin Ukrainian Orthodox Church",40.576175,-79.765398},
    {"First Church of God",40.576347,-79.764044},
    {"Arnold Firemen Memorial Park",40.578755,-79.771688},
    {"City of Arnold",40.580041,-79.767265},
    {"Arnold Volunteer Engine Co. #2 Memorial",40.579746,-79.762123},
    {"John 15:13 Monument",40.581383,-79.753979},
    {"Holy Martyrs Church",40.600008,-79.765682},
    {"Bethel Church",40.599627,-79.76275},
    {"Slovak American Club",40.600244,-79.760636},
    {"First United Presbyterian Church",40.604467,-79.756324},
    {"Community Library of Allegheny",40.601752,-79.753934},
    {"Tarentum WW1 Memorial",40.600038,-79.751809},
    {"Tarentum Pavillion",40.601131,-79.74887},
    {"Tarentum Fire Department Memorial",40.601384,-79.748058},
    {"War Memorial",40.60264,-79.742881},
    {"First Pentecostal Church",40.604371,-79.741305},
    {"Trinity United Methodist Church",40.610712,-79.748121},
    {"Shiloh Baptist Church",40.609529,-79.741591},
    {"Dinosaur Art Statue",40.613494,-79.742653},
    {"Calvary Baptist Church",40.614176,-79.7369},
    {"The Virgin Mary and Joseph the Carpenter",40.611791,-79.723725},
    {"Word Of Faith Church",40.61357,-79.722159},
    {"Natrona Recreational Park",40.613645,-79.720069},
    {"Community Library of Allegheny",40.620677,-79.728314},
    {"Fallen Firemen Memorial",40.621407,-79.732776},    
  };


// Good
// 0.006

// Bad
//

const double kScanRadius = 0.007;

struct ScanPoint
{
  double x_;
  double y_;
  int numberGyms_;
};

typedef std::vector<ScanPoint> ScanPointList;

class Point{
public:
  double x, y;
  Point(double px, double py) {
    x = px;
    y = py;
  }
  Point sub(Point p2) {
    return Point(x - p2.x, y - p2.y);
  }
  Point add(Point p2) {
    return Point(x + p2.x, y + p2.y);
  }
  double distance(Point p2) {
    return sqrt((x - p2.x)*(x - p2.x) + (y - p2.y)*(y - p2.y));
  }
  Point normal() {
    double length = sqrt(x*x + y*y);
    return Point(x/length, y/length);
  }
  Point scale(double s) {
    return Point(x*s, y*s);
  }
};

class Circle {
public:
  double x, y, r, left;
  Circle(double cx, double cy, double cr) {
    x = cx;
    y = cy;
    r = cr;
    left = x - r;
  }
  std::pair<Point, Point> intersections(Circle c) {
    Point P0(x, y);
    Point P1(c.x, c.y);
    double d, a, h;
    d = P0.distance(P1);
    a = (r*r - c.r*c.r + d*d)/(2*d);
    h = sqrt(r*r - a*a);
    Point P2 = P1.sub(P0).scale(a/d).add(P0);
    double x3, y3, x4, y4;
    x3 = P2.x + h*(P1.y - P0.y)/d;
    y3 = P2.y - h*(P1.x - P0.x)/d;
    x4 = P2.x - h*(P1.y - P0.y)/d;
    y4 = P2.y + h*(P1.x - P0.x)/d;

    return std::pair<Point, Point>(Point(x3, y3), Point(x4, y4));
  }

};


int countNumberGymsNear(Point centerPoint)
{
  int gymCount = 0;
  
  for (auto gym : kGymList)
    {
      Point gymPoint(gym.x_, gym.y_);

      double dist = gymPoint.distance(centerPoint);

      if (dist < kScanRadius + std::numeric_limits<float>::epsilon())
	{
	  ++gymCount;
	}
    }
  
  return gymCount;
}

int main(int argc, char *argv[]) {

  ScanPointList scanPointList;
  
  for (size_t a = 0; a < kGymList.size(); ++a)
    {
      for (size_t b = a + 1; b < kGymList.size(); ++b)
	{
	  Circle kGymACircle(kGymList[a].x_, kGymList[a].y_, kScanRadius);
	  Circle kGymBCircle(kGymList[b].x_, kGymList[b].y_, kScanRadius);

	  auto kGymInterections = kGymACircle.intersections(kGymBCircle);

	  {
	    if (!std::isnan(kGymInterections.first.x))
	      {
		// std::cout << "GymA = " << kGymList[a].Name_ << ", GymB = " << kGymList[b].Name_ << std::endl;

		// std::cout << "Interects at " <<
		//   kGymInterections.first.x << ", " << 
		//   kGymInterections.first.y << std::endl;


		auto kNumberOfGymsNear = countNumberGymsNear(kGymInterections.first);

		ScanPoint scanPoint = {kGymInterections.first.x, kGymInterections.first.y, kNumberOfGymsNear};

		scanPointList.push_back(scanPoint);		
	      }
	  }

	  {
	    if (!std::isnan(kGymInterections.second.x))
	      {
		// std::cout << "GymA = " << kGymList[a].Name_ << ", GymB = " << kGymList[b].Name_ << std::endl;

		// std::cout << "Interects at " <<
		//   kGymInterections.second.x << ", " << 
		//   kGymInterections.second.y << std::endl;


		auto kNumberOfGymsNear = countNumberGymsNear(kGymInterections.second);

		ScanPoint scanPoint = {kGymInterections.second.x, kGymInterections.second.y, kNumberOfGymsNear};

		scanPointList.push_back(scanPoint);		
	      }
	  }
	}
    }

  for (auto scanPoint : scanPointList)
    {
      std::cout << scanPoint.numberGyms_ << " " << "https://gymhuntr.com/#" << scanPoint.x_ << "," << scanPoint.y_ << std::endl;
      
    }
  
}
