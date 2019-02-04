/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:05:33 by axbal             #+#    #+#             */
/*   Updated: 2019/01/30 12:11:13 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"

# define LA 1152
# define HA 648
# define FOV 90
# define SCENES_PATH "./scenes/"
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define CUBE 5

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_color;

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_dot
{
	float			x;
	float			y;
	float			z;
}					t_dot;

typedef struct		s_cam
{
	float			px;
	float			py;
	float			pz;
	float			rx;
	float			ry;
	float			rz;
}					t_cam;

typedef struct		s_light
{
	float			px;
	float			py;
	float			pz;
	int				intensity;
}					t_light;

typedef struct		s_obj
{
	int				type;
	float			px;
	float			py;
	float			pz;
	float			radius;
	float			angle;
	float			size;
	t_vec			*v;
	int				rx;
	int				ry;
	t_color			color;
	float			lim_x_neg;
	float			lim_x_pos;
	float			lim_y_neg;
	float			lim_y_pos;
	float			lim_z_neg;
	float			lim_z_pos;
	int				lim_x_c;
	int				lim_y_c;
	int				lim_z_c;
	int				size_c;
	int				pos_c;
	int				type_c;
	int				radius_c;
	int				angle_c;
	int				vector_c;
	int				rotation_c;
	int				shiny;
}					t_obj;

typedef struct		s_img
{
	void			*ptr;
	char			*str;
	int				width;
	int				height;
	int				bpp;
	int				s_l;
	int				endian;
	int				sp;
}					t_img;

typedef struct		s_data
{
	char			*file_name;
	void			*mlx_ptr;
	void			*win_ptr;
	int				current_img;
	t_img			*img0;
	t_img			*img;
	t_img			*img2;
	t_obj			**obj;
	t_light			**light;
	t_cam			*cam;
	t_vec			**rays;
	t_color			**pix_col;
	int				lights;
	int				objects;
	float			s_xmin;
	float			s_ymin;
	float			s_xmax;
	float			s_ymax;
	int				l;
	float			t[2];
	int				stop;
	t_color			a;
	t_color			green;
	t_color			red;
	t_color			blue;
	int				selected_choice;
	int				selected_option;
	int				menu;
	int				dir_files;
	char			**files;
}					t_data;

typedef struct		s_hdr
{
	char			type[2];
	int				file_size;
	int				rsrvd;
	int				offset;
	int				size;
	int				plane_nb;
	int				compression;
	int				h_res;
	int				v_res;
	int				color_nb;
	int				imp_color_nb;
	int				i_size;
	int				bpp;
	int				la;
	int				ha;
}					t_hdr;

typedef struct		s_rtc
{
	int				obj_i;
	int				i;
	int				j;
	float			dm;
	t_obj			*o;
	float			stamp;
}					t_rtc;

typedef struct		s_diffuse
{
	t_vec			normale;
	t_vec			lo;
	t_vec			a_dot;
	t_dot			obj_center;
	t_dot			lc;
	t_dot			affixe;
	float			angle;
}					t_diffuse;

typedef struct		s_sec_r
{
	t_dot			ld;
	t_vec			lo;
	t_vec			o_ray;
	float			dist;
	int				i;
	t_dot			inter;
}					t_sec_r;

void				ft_fail(char *str, t_data *data);
void				ft_return(char *str, t_data *data);
int					read_file(t_data *data, char *file);
float				ft_atof(const char *str);
float				*three_values_tab(char *f, int s);
int					read_light(t_data *data, char *file, int select);
char				*word_return(char *str, int select);
int					read_camera(t_data *data, char *file, int select);
int					read_object(t_data *d, char *f, int s);
int					get_object_type(char *f, int s, t_obj *obj);
int					get_object_pos(char *f, int s, t_obj *obj);
int					get_object_rad(char *f, int s, t_obj *obj);
int					get_object_angle(char *f, int s, t_obj *obj);
int					get_object_rot(char *f, int s, t_obj *obj);
int					get_object_vec(char *f, int s, t_obj *obj);
int					get_object_color(char *f, int s, t_obj *obj);
int					get_object_size(char *f, int s, t_obj *obj);
t_obj				*create_object(t_data *data);
int					key_release(int key, void *d);
int					ft_increase_file(char **file, char *line);
char				*start_reading(char *str);
int					close_program(t_data *d);
int					refresh_expose(t_data *d);
void				start_raytracing(t_data *d);
t_vec				two_point_vector(t_dot p1, t_dot p2);
void				norm_vec(t_vec *to_normalize);
void				put_pixel_to_image(t_dot o, t_data *d, char *i, t_color c);
t_dot				new_dot(float x, float y, float z);
t_vec				new_vec(float x, float y, float z);
t_data				*new_data(void);
t_color				new_color(int r, int g, int b, int a);
void				gen_rays(t_data *d);
t_img				*init_img(t_data *data);
float				scalar(t_vec *v1, t_vec *v2);
t_vec				trans_vec(t_vec vec, float tx, float ty, float tz);
t_vec				rot_vec(t_vec ray, float rx, float ry, float rz);
float				degree_to_radian(float degree);
float				ft_clamp(float to_clamp, float min, float max);
t_dot				get_hitpoint(t_vec vector, float d, t_data *data);
t_color				secondary_rays(t_dot inter, t_data *d, t_obj *obj, t_vec r);
int					test_object(t_data *d, t_vec ray, t_obj *obj);
int					test_light(t_data *d, t_light *l, t_sec_r s, t_obj *obj);
float				two_point_dist(t_dot p1, t_dot p2);
t_color				color_interp(t_color c1, t_color c2, float factor);
int					get_object_lim_x(char *f, int s, t_obj *obj);
int					get_object_lim_y(char *f, int s, t_obj *obj);
int					get_object_lim_z(char *f, int s, t_obj *obj);
int					check_lim(t_obj *o, t_dot dot);
int					double_check_lim(t_obj *o, t_dot d1, t_dot d2);
int					cmp_dot(t_dot d1, t_dot d2);
t_dot				dot_from_light(t_light *l, t_vec vec, float dist);
float				find_right_distance(t_data *d, t_dot l, t_vec v, t_dot i);
int					call_side_light_check(t_sec_r s, t_obj *obj, t_data *d);
t_color				apply_color(t_color c, t_obj *o, t_data *d, float angle);
t_color				find_diffuse(t_color c, t_dot inter, t_obj *obj, t_data *d);
int					test_object(t_data *d, t_vec ray, t_obj *obj);
float				pick_a_side(float dm, t_vec ray, t_obj *o, t_data *d);
void				fswap(float *f1, float *f2);
void				fabricated_object(t_data *d, t_obj *obj);
void				add_obj(t_data *data, t_obj *obj);
int					screenshot(t_data *d);
char				*get_file_name(char *str);
void				free_data(t_data *d);
void				set_up_menu(t_data *d);
int					open_scenes_dir(t_data *d);
int					write_menu(t_data *d);
void				draw_menu0(t_img *img, t_data *d);
int					check_file(t_data *d, char *file);
int					open_selected_choice(t_data *d);
void				loading_screen_bar(t_data *d);
t_color				real_lerp(t_color c1, t_color c2, float factor);
void				init_data(t_data *n);
void				reset_colors(t_data *d);
int					color_diff(t_color c1, t_color c2);

#endif
