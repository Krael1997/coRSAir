# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelrodr <abelrodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 12:05:22 by abelrodr          #+#    #+#              #
#    Updated: 2023/05/02 15:52:06 by abelrodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = /Users/abelrodr/.brew/opt/openssl@3.1/include
LIB = /Users/abelrodr/.brew/opt/openssl@3.1/lib
CFLAGS = -Wall -Wextra -Werror -Wno-deprecated-declarations

all:
	@clear
	gcc coRSAir.c $(CFLAGS) -I$(INC) -L$(LIB) -lssl -lcrypto -o coRSAir
	@./coRSAir ./resources/cert1.pem ./resources/cert2.pem ./resources/passwd.enc