#include "includes/cub3d.h"
double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}
int main()
{
    double n = 10 * M_PI;
    printf("%f", normalize_angle(n));
}