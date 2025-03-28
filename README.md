double posX = 22, posY = 12; | x and y start position
double dirX = -1, dirY = 0; | initial direction vector
double planeX = 0, planeY = 0.66; | the 2d raycaster version of camera plane

double time = 0; //time of current frame
double oldTime = 0; //time of previous frame

for(int x = 0; x < screen_width; x++)
      //calculate ray position and direction
      double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;

//calculate ray position and direction
double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
double rayDirX = dirX + planeX * cameraX;
double rayDirY = dirY + planeY * cameraX;

deltaDistX = abs(1 / rayDirX)
deltaDistY = abs(1 / rayDirY) 

//which box of the map we're in
int mapX = int(posX);
int mapY = int(posY);
//length of ray from current position to next x or y-side
double sideDistX;
double sideDistY;
//length of ray from one x or y-side to next x or y-side
double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
double perpWallDist;
//what direction to step in x or y-direction (either +1 or -1)
int stepX;
int stepY;
int hit = 0; //was there a wall hit?
int side; //was a NS or a EW wall hit?

//calculate step and initial sideDist
if (rayDirX < 0)
{
  stepX = -1;
  sideDistX = (posX - mapX) * deltaDistX;
}
else
{
  stepX = 1;
  sideDistX = (mapX + 1.0 - posX) * deltaDistX;
}
if (rayDirY < 0)
{
  stepY = -1;
  sideDistY = (posY - mapY) * deltaDistY;
}
else
{
  stepY = 1;
  sideDistY = (mapY + 1.0 - posY) * deltaDistY;
}

//perform DDA
while (hit == 0)
{
  //jump to next map square, either in x-direction, or in y-direction
  if (sideDistX < sideDistY)
  {
    sideDistX += deltaDistX;
    mapX += stepX;
    side = 0;
  }
  else
  {
    sideDistY += deltaDistY;
    mapY += stepY;
    side = 1;
  }
  //Check if ray has hit a wall
  if (worldMap[mapX][mapY] > 0) hit = 1;
}

//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
if(side == 0) perpWallDist = (sideDistX - deltaDistX);
else          perpWallDist = (sideDistY - deltaDistY);

//Calculate height of line to draw on screen
int lineHeight = (int)(h / perpWallDist);

//calculate lowest and highest pixel to fill in current stripe
int drawStart = -lineHeight / 2 + h / 2;
if(drawStart < 0)drawStart = 0;
int drawEnd = lineHeight / 2 + h / 2;
if(drawEnd >= h)drawEnd = h - 1;