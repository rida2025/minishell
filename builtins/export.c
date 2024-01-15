/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:18:49 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/13 13:11:23 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open the file for writing
    int fd = open("     .txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Replace standard output with the file
    if (dup2(fd, 1) == -1) {
        perror("dup2");
        return 1;
    }

    // Now anything written to standard output will go to the file
    printf("Hello, World\n");

    return 0;
}