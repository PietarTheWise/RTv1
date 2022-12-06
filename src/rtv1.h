/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pietari <pietari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:16:03 by vkuksa            #+#    #+#             */
/*   Updated: 2022/12/01 01:30:53 by pietari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include "libft.h"

# define PLANE		0
# define SPHERE		1
# define CONE		2
# define CYLINDER	3

union	u_colour
{
	unsigned int	number;
	unsigned char	channels[4];
};

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}				t_vec;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}				t_ray;

typedef struct s_cone
{
	union u_colour	color;
	t_vec			top;
	t_vec			bottom;
	t_vec			side_point;
	t_vec			hit_point;
	t_vec			h;
	t_vec			subtr_top_bot;
	float			m;
	float			t0;
	float			t1;
	float			radius;
	float			light_level;
	float			discr;
	float			height;
	float			dot_product;
	int				end;
	t_vec			rotation;
	t_vec			translation;
}				t_cone;

typedef struct s_cylinder
{
	union u_colour	color;
	t_vec			top;
	t_vec			bottom;
	t_vec			side_point;
	t_vec			hit_point;
	t_vec			h;
	float			dot_product;
	float			t0;
	float			t1;
	float			radius;
	float			light_level;
	float			discr;
	float			height;
	int				end;
	t_vec			rotation;
	t_vec			translation;
}				t_cylinder;

typedef struct s_plane
{
	t_vec			center;
	t_vec			normal;
	t_vec			hit_point;
	union u_colour	color;
	int				end;
	float			light_level;
	float			hit;
	float			intersect;
	t_vec			rotation;
	t_vec			translation;
}				t_plane;

typedef struct s_sphere
{
	t_vec			center;
	t_vec			camera_to_center;
	t_vec			hit_point;
	t_vec			translation;
	union u_colour	color;
	float			radius;
	float			light_level;
	int				end;
	float			hit;
	float			tca;
	float			d;
	float			thc;
	float			t0;
	float			t1;
	float			discr;
}				t_sphere;

typedef struct s_util
{
	char			**values;
	char			**translation;
	char			**center;
	char			**c_normal;
	char			**colors;
	char			**top;
	char			**bottom;
	char			**radius;
	float			hit;
	float			tca;
	float			d;
	float			thc;
	float			infinite;
	float			t0;
	float			t1;
	float			light_level;
	float			light_level_plane;
	float			shadow_length;
	float			camera_angle_x;
	float			camera_angle_y;
	float			camera_angle_z;
	int				x;
	int				y;
	int				plane_hit_index;
	int				sphere_hit_index;
	float			a;
	float			b;
	float			c;
	float			q;
	int				closest_sphere;
	int				closest_cylinder;
	int				closest_cone;
	int				closest_plane;
	int				closest;
	int				sphere_amount;
	int				plane_amount;
	int				cone_amount;
	int				cylinder_amount;
	int				light_found;
	int				camera_found;
	float			alpha;
	float			ndc_x;
	float			ndc_y;
	float			pixel_screen_x;
	float			pixel_screen_y;
	float			img_ratio;
	union u_colour	gbr;
	t_ray			ray;
	t_ray			light;
	t_vec			light_translation;
	t_vec			camera_translation;
	t_plane			plane;
	t_plane			*planes;
	t_sphere		*spheres;
	t_vec			normal;
	t_vec			hit_point;
	t_vec			shadow_hit_point;
	t_vec			w;
	t_cone			*cones;
	t_cylinder		*cylinders;
	t_ray			shadow;
}			t_util;

typedef struct s_sdl
{
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	SDL_Texture		*buffer;
	void			*data;
	int				pitch;
}	t_sdl;

t_vec			subtract(t_vec v_one, t_vec v_two);
float			intersectPlane(const t_plane plane, const t_ray ray, float t);
float			dot_product(t_vec v_one, t_vec v_two);
float			vec_len(t_vec vector);
t_vec			vec_add(t_vec v_one, t_vec v_two);
t_vec			vec_normalize(t_vec vector);
t_vec			vec_pow(t_vec vector);
t_vec			vec_scale(t_vec vector, float scaler);
t_vec			vector(float x, float y, float z);
int				level_color(union u_colour color, float light_level);
void			set_color(int r, int g, int b, union u_colour *color);
t_sphere		*initiate_spheres(int amount);
t_cone			*initiate_cones(int amount);
t_plane			*initiate_planes(int amount);
t_cylinder		*initiate_cylinders(int amount);
t_vec			calculate_direction(t_util utils, float x, float y);
void			cone_calculation(t_util utils, t_cone *cone);
void			cylinder_calculation(t_util utils, t_cylinder *cyl);
void			sphere_calculation(t_util utils, t_sphere *sphere);
void			sphere_assign(char *line, t_util *utils);
void			plane_assign(char *line, t_util *utils);
void			cone_assign(char *line, t_util *utils);
void			cylinder_assign(char *line, t_util *utils);
void			light_assign(char *line, t_util *utils);
void			camera_assign(char *line, t_util *utils);
void			check_given_values(char **values, int needed_amount);
void			check_char_vector(char **xyz);
void			check_float_vals(char *predot, char *postdot);
void			rotation_x(t_vec *direction, float angle);
void			rotation_y(t_vec *direction, float angle);
void			rotation_z(t_vec *direction, float angle);
int				sphere_hit(t_util utils, t_sphere sphere);
int				cone_hits(t_util utils, t_cone cone);
int				cylinder_hit(t_util utils, t_cylinder cyl);
void			check_line(char *line);
void			vector_assign(char **coords, int i, t_vec *xyz);
void			calculate_light_cylinder(t_util *utils,
					t_ray light, t_cylinder cylinder);
int				check_if_inside(t_util utils);
void			check_duplicate_cylinder(t_util *utils);
void			draw_sphere(void *data, t_util *utils);
void			draw_plane(void *data, t_util *utils);
void			draw_cone(void *data, t_util *utils);
void			draw_cylinder(void *data, t_util *utils);
void			check_objects_and_draw(void *data, t_util *utils);
void			put_pixel(void *data, int x, int y, int color);
void			look_for_closest(t_util *utils);
void			check_for_shadows(void *data, t_util utils, int flag);
void			plane_shadow(void *data, t_util utils,
					int flag, int shadow_color);
void			cylinder_shadow(void *data, t_util utils,
					int flag, int shadow_color);
void			cone_shadow(void *data, t_util utils,
					int flag, int shadow_color);
void			sphere_shadow(void *data, t_util utils,
					int flag, int shadow_color);
float			plane_hit(t_plane plane, const t_ray shadow,
					float shadow_length, t_util utils);
void			init_objects(int argc, char **argv, t_util *utils);
void			assign_object_values(t_util *utils, char *file);
void			check_each_line(t_util *utils, char *line);
void			assign_object_mallocs(t_util *utils);
void			default_cam_and_light(t_util *utils);
int				get_object_amount(t_util *utils, char *file);
void			object_amount_util(int *ret, int *i, int *fd, char *file);
float			check_closest_plane(t_util *utils);
float			check_closest_sphere(t_util *utils);
float			check_closest_cone(t_util *utils);
float			check_closest_cylinder(t_util *utils);
int				closest_cylinder(t_util *utils);
int				closest_cone(t_util *utils);
int				closest_sphere(t_util *utils);
int				closest_plane(t_plane *planes, t_util *utils);
void			check_planes(t_util utils, t_plane *plane,
					t_ray light, float hit);
float			intersect_plane(t_plane plane, const t_ray ray, float t);
void			check_spheres(t_util utils, t_sphere *sphere,
					t_ray light);
void			calculate_light_level(t_util *utils, float t0,
					t_vec center, t_ray light);
void			calculate_light_cone(t_util *utils,
					int i, t_ray light);
float			plane_hit(t_plane plane, const t_ray shadow,
					float shadow_length, t_util utils);
void			light_plane_correction(t_util *utils);
void			vector_assign_util(char **coords,
					int pre_point, int *index, int i);
void			read_rotations(char *rotate_str, t_vec *rotation);
void			rotation_xyz(t_vec *direction, float angle_x,
					float angle_y, float angle_z);
void			translation_unit(t_util *utils);
void			sdl_buffer(t_sdl sdl);
void			sdl_init(t_sdl *sdl);
void			assign_object_mallocs(t_util *utils);
void			free_sphere_str(t_util *utils);
void			free_cone_str(t_util *utils);
void			free_plane_str(t_util *utils);
void			free_cylinder_str(t_util *utils);

#endif
