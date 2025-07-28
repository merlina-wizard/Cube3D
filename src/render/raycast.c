#include "cube3d.h"
#include <math.h>

static void init_dir_and_delta(t_game *g, t_ray *r, int x)
{
    double cameraX = 2.0 * x / (double)g->win_w - 1.0;
    r->rayDirX = g->player.dir_x + g->player.plane_x * cameraX;
    r->rayDirY = g->player.dir_y + g->player.plane_y * cameraX;
    r->mapX = (int)g->player.x;
    r->mapY = (int)g->player.y;
    r->deltaDistX = fabs(1.0 / r->rayDirX);
    r->deltaDistY = fabs(1.0 / r->rayDirY);
}

static void init_step(t_game *g, t_ray *r)
{
    if (r->rayDirX < 0)
    {
        r->stepX = -1;
        r->sideDistX = (g->player.x - r->mapX) * r->deltaDistX;
    }
    else
    {
        r->stepX = 1;
        r->sideDistX = (r->mapX + 1.0 - g->player.x) * r->deltaDistX;
    }
    if (r->rayDirY < 0)
    {
        r->stepY = -1;
        r->sideDistY = (g->player.y - r->mapY) * r->deltaDistY;
    }
    else
    {
        r->stepY = 1;
        r->sideDistY = (r->mapY + 1.0 - g->player.y) * r->deltaDistY;
    }
}

static void init_ray(t_game *g, t_ray *r, int x)
{
    init_dir_and_delta(g, r, x);
    init_step(g, r);
    r->hit = 0;
}

static void step_dda(t_game *g, t_ray *r)
{
    while (r->hit == 0)
    {
        if (r->sideDistX < r->sideDistY)
        {
            r->sideDistX += r->deltaDistX;
            r->mapX += r->stepX;
            r->side = 0;
        }
        else
        {
            r->sideDistY += r->deltaDistY;
            r->mapY += r->stepY;
            r->side = 1;
        }
        if (g->map.grid[r->mapY][r->mapX] == '1')
            r->hit = 1;
    }
}

static void compute_perp_dist(t_game *g, t_ray *r)
{
    if (r->side == 0)
        r->perp_dist = (r->mapX - g->player.x + (1 - r->stepX) / 2.0)
                      / r->rayDirX;
    else
        r->perp_dist = (r->mapY - g->player.y + (1 - r->stepY) / 2.0)
                      / r->rayDirY;
}

void cast_ray(t_game *g, int x)
{
    t_ray *r = &g->ray;
    init_ray(g, r, x);
    step_dda(g, r);
    compute_perp_dist(g, r);
}

void draw_wall_slice(t_game *g, int x, t_ray *r)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int y;
    int color;

    lineHeight = (int)(g->win_h / r->perp_dist);
    drawStart = -lineHeight / 2 + g->win_h / 2;
    if (drawStart < 0)
        drawStart = 0;
    drawEnd = lineHeight / 2 + g->win_h / 2;
    if (drawEnd >= g->win_h)
        drawEnd = g->win_h - 1;
    color = g->texture[r->side].data[0];
    if (r->side == 1)
        color = (color >> 1) & 0x7F7F7F;
    y = drawStart;
    while (y <= drawEnd)
    {
        int *pixel = (int *)(g->frame.data
            + y * g->frame.size_line
            + x * 4);
        *pixel = color;
        y++;
    }
}
