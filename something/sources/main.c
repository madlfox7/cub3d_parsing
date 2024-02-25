#include "cub3d.h"

#include <string.h>


int main(int argc, char **argv) 
{
    struct game Game;
   ft_check_argc_and_name(argc, argv);
    ft_get_map(argv[1], &Game); 
    ft_check_map(&Game); 
  printf("MAP IS VALID\n");
  free_map(&Game);
   print_attributes(&Game);
  free_attributes(&Game);
  return 0;
}

/////////////////////////////////


void free_map(struct game *Game)
{
    if (!Game->map)
        return ;
    if (Game->map != NULL)
    {
        for (int i = 0; i < Game->height; i++)
            free(Game->map[i]);
        free(Game->map);
    }
}


void pars_attribute_lines(struct game *Game, int fd, int *map_start)
{
    char *line;
    while ((line = get_next_line(fd)))
    {
        if (is_attribute(Game, line))
        {
            free(line);
            (*map_start)++;
        } 
        else
        {
            free(line);
            break;
        }
    }
}

void read_map_dimensions(int fd, struct game *Game)
{
        Game->height++;
    int max_width = 0;
    int line_len = 0;
    char *line = NULL;

  //  printf("\nMAP STARTS FROM [%s]\n", get_next_line(fd));
    while ((line = get_next_line(fd)) != NULL)
    {
        Game->height++;  
        line_len = strlen(line);
        if (line_len > max_width)
        {
            max_width = line_len;
            Game->width = max_width; 
        }
        free(line);
    }

    printf("\nHEIGHT=%d WIDTH=%d\n", Game->height, Game->width);
}

void allocate_map_memory(struct game *Game)
{
        Game->map = (char **)calloc(Game->height, sizeof(char *));
    if (Game->map == NULL) 
    {
        ft_put_error("Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

}

void copy_map_lines(int fd, struct game *Game)
{
    char *line = NULL;
    int line_count = 0;
     
    while ((line = get_next_line(fd)))
    {
        if (inv_sym(line))
        {
            ft_put_error("Error: Invalid symbol found");
            exit(EXIT_FAILURE);
        }
        Game->map[line_count] = calloc(Game->width + 1, sizeof(char)); // +1  null
        if (Game->map[line_count] == NULL) //calloc error
        {
            ft_put_error("Error: Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        strncpy(Game->map[line_count], line, strlen(line)); 
        free(line);
        line_count++;
    }
}



void check_map_empty(struct game *Game)
{
    if (Game->height == 0 || Game->width == 0)
    {
        ft_put_error("Error: Empty map");
        exit(EXIT_FAILURE);
    }
}


void print_attributes(struct game *Game)
{
    printf("PRINTING attr\n");
    printf("NO [%s]\n", Game->attr.no);
    printf("SO [%s]\n", Game->attr.so);
    printf("WE [%s]\n", Game->attr.we);
    printf("EA [%s]\n", Game->attr.ea);
    printf("F [%s]\n", Game->attr.f);
    printf("C [%s]\n", Game->attr.c);
}


void ft_get_map(char *argv, struct game *Game)
{
    init_attributes(Game); 
    printf("Getting map\n");
    int fd;
    check_file_exists(argv, &fd);
   
    int map_start = 0;
    pars_attribute_lines(Game, fd, &map_start);

    
   
     read_map_dimensions(fd, Game);

     printf("\nHEIGHT=%d WIDTH=%d\n", Game->height, Game->width);
     close(fd); 
     allocate_map_memory(Game);
     fd = open(argv, O_RDONLY);
    check_file_exists(argv, &fd);
    printf("MAP STARTS FROM [%d] line\n", map_start); 
    char *line = NULL;
       while ((line = get_next_line(fd)) && map_start > 1)
    {
        free(line); // Skipping attribute lines
        map_start--;
    }
    printf("MAP BEGINS HERE\n");

    copy_map_lines(fd, Game);
    check_map_empty(Game);
    ft_print_map(Game);
    printf("MAP END\n");
    close(fd);
}


void ft_print_map(struct game *Game) //don't need this later
{
    printf("Printing map\n");
    for (int i = 0; i < Game->height; i++)
    {
        printf("%s", Game->map[i]);
    }
    //printf("\n");
     printf("Height: %d\n", Game->height);
    printf("Width: %d\n", Game->width);
}



void	ft_put_error(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		write(STDERR_FILENO, &string[i], 1);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}



// void ft_get_map(char *argv, struct game *Game) //old
// {
//     init_attributes(Game);
//     printf("Getting map\n");
//     int fd;
//     check_file_exists(argv, &fd); // Check if it's a file not a directory

//     // Crop Map
//     int map_start = 0;
//     char *line = NULL;

//     while ((line = get_next_line(fd)))
//     {
//         if (is_attribute(Game, line)) //if line starts from attribute 
//         {
//             printf("[%s]\n", line);
//                 free(line);  
//               map_start++;
//         }
//         else
//             break;
//     }




//     printf("MAP STARTS FROM [%d] line\n", map_start); 
// //    check_attr_path(Game);
    

//   printf("PRINTING attr\n");
//     printf("NO [%s]\n", Game->attr.no);
//     printf("SO [%s]\n", Game->attr.so);
//     printf("WE [%s]\n", Game->attr.we);
//     printf("EA [%s]\n", Game->attr.ea);
//     printf("F [%s]\n", Game->attr.f);
//     printf("C [%s]\n", Game->attr.c);
//     Game->height++;
//     int max_width = 0;
//     int line_len = 0;

//   //  printf("\nMAP STARTS FROM [%s]\n", get_next_line(fd));
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         Game->height++;  
//         line_len = strlen(line);
//         if (line_len > max_width)
//         {
//             max_width = line_len;
//             Game->width = max_width; 
//         }
//         free(line);
//     }

//     printf("\nHEIGHT=%d WIDTH=%d\n", Game->height, Game->width);

//     close(fd); 

//     Game->map = (char **)calloc(Game->height, sizeof(char *));
//     if (Game->map == NULL) 
//     {
//         ft_put_error("Error: Memory allocation failed");
//         exit(EXIT_FAILURE);
//     }

//     fd = open(argv, O_RDONLY);
//     check_file_exists(argv, &fd);

//     while ((line = get_next_line(fd)) && map_start > 1)
//     {
//         free(line); // Skipping attribute lines
//         map_start--;
//     }
//     printf("MAP BEGINS HERE\n");

//     int line_count = 0;
     
//     while ((line = get_next_line(fd)))
//     {
//         if (inv_sym(line))
//         {
//             ft_put_error("Error: Invalid symbol found");
//             exit(EXIT_FAILURE);
//         }
//         Game->map[line_count] = calloc(Game->width + 1, sizeof(char)); // +1  null
//         if (Game->map[line_count] == NULL) //calloc error
//         {
//             ft_put_error("Error: Memory allocation failed");
//             exit(EXIT_FAILURE);
//         }
//         strncpy(Game->map[line_count], line, strlen(line)); 
//         free(line);
//         line_count++;
//     }
//     ft_print_map(Game);
//     printf("MAP END\n");
//     close(fd);
// }

