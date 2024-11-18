# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    build.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/04 20:18:14 by rgramati          #+#    #+#              #
#    Updated: 2024/11/14 00:11:01 by rgramati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

set -xe

make so

gcc -Wall -Wextra -o term main.c -L. -Llib/cmem -lterm -lcmem -lm  -I include -I lib/cmem/include -g3 -Wl,-rpath,./:./lib/cmem/
