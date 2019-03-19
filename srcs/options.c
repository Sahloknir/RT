#include "rt.h"

void	switch_option2(int option, t_data *d)
{
	if (option == 4)
		d->img->crtn = d->img->crtn > 0 ? 0 : 1;
	else if (option == 5)
		d->img->d4 = d->img->d4 > 0 ? 0 : 1;
	else if (option == 6)
	{
		if (d->img->d5 == 0)
			d->img->d5 = 30;
		d->img->d5 -= 10;
	}
	refresh_expose(d);
}

void	switch_option(int option, t_data *d)
{
	if (option == 1)
	{
		d->img->sp = d->img->sp > 0 ? 0 : 1;
		d->img->gs = 0;
	}
	else if (option == 2)
	{
		d->img->gs = d->img->gs > 0 ? 0 : 1;
		d->img->sp = 0;
	}
	else if (option == 3)
	{
		if (d->img->d == 2)
			d->img->d = -1;
		d->img->d += 1;
	}
	switch_option2(option, d);
}

int		select_option(int key, t_data *d)
{
	if (d->current_img != 0)
		return (-1);
	if (d->selected_option == -1 && key == 125)
		d->selected_option = 0;
	else if (d->selected_option == 0 && key == 126)
		d->selected_option = -1;
	if (d->selected_option == 0 && key == 36)
		d->selected_option = 1;
	else if (d->selected_option > 0)
	{
		if (key == 12)
		{
			d->selected_option = -1;
			ft_return(NULL, d);
		}
		if (key == 36)
			switch_option(d->selected_option, d);
		if (key == 125 && d->selected_option < 6)
			d->selected_option += 1;
		if (key == 126 && d->selected_option > 1)
			d->selected_option -= 1;
	}
	refresh_expose(d);
	return (1);
}
