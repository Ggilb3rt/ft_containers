# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile.settings.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 21:06:11 by rotrojan          #+#    #+#              #
#    Updated: 2022/04/28 17:28:51 by lusokol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# The name of the binary
NAME = container

# sources needed to compile (without the path)
SRC =	main.cpp \

# path of sources
PATH_SRCS = mains

# pathe of includes
INCLUDES = containers

# flags for compilation
CXXFLAGS = #-Wall -Wextra -Werror

# compiler used
CXX = c++
