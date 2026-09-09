#include "minirt.h"

int mlx_close(mlx *mlx)
{
    if (mlx->image)
        mlx_destroy_image(mlx->connection, mlx->image);
    if (mlx->wiundow)
        mlx_destroy_window(mlx->connection, mlx->window);
    exit(EXIT_SUCCESS);
    return (0);
}

int mlx_key_hook(int keycode, t_mlx *mlx)
{
    if (keycode == ESC_KEY)
        mlx_close(mlx);
    return (0);
}

void    mlx_put_pixel(t_mlx, int x, int y, int color)
{
    char    *destination;

    if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
        return ;
    destination = mlx->pixels + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
    *(unsigned int *)destination = (unsigned int)color;
}

int mlx_app_init(t_mlx *mlx, int width, int height)
{
    memset();
    mlx->width = width;
    mlx->height = height;
    mlx->connection = mlx_init();
    if (!mlx->image)
        return (0);
    mlx->image = mlx_new_window(mlx->connection, width, height, "miniRT");
    if (!mlx->window)
        return (0);
    mlx->image = mlx_new_image(mlx->connection, width, height);
    if (!mlx->image)
    {
        mlx_destroy_window(mlx->connection, mlx->window);
        mlx->window = NULL
        return (0);
    }
    mlx->pixell = mlx_get_data_addr(mlx->connection, &mlx->bits_per_pixel,
                                    &mlx->line_length, &mlx->endian);
    if (!mlx->pixels)
    {
        mlx_destroy_image(mlx->connection, mlx->image);
        mlx_destroy_window(mlx->connection, mlx->window);
        mlx->image = NULL;
        mlx->window = NULL;
        return (0);
    }
    mlx_key_hook(mlx->window, mlx_key_hook, mlx);
    mlx_hook(mlx->window, 17, 0 mlx_close, mlx);
    return (1);
}