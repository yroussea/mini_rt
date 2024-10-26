; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_write.s                                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2024/03/15 19:05:42 by kiroussa          #+#    #+#              ;
;    Updated: 2024/03/27 21:19:36 by kiroussa         ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%define SYS_WRITE 1

section .text
	global ft_write

ft_write:							; ssize_t ft_write(int fd, char *buffer, size_t size)
	cmp edi, 0						; if (fd < 0)
	jl .ret							;	goto .bad_fd

	cmp rsi, 0						; if (buffer == NULL)
	je .ret							;	goto .bad_buf

	mov rax, SYS_WRITE				; rax = sys_write
	syscall 						; _write()
	
	cmp eax, 0						; if (sys_ret >= 0)
	jge .ret						;	goto .ret

	; Error handling
	mov r11, rax					; error_value = sys_ret
	neg r11							; error_value = -error_value
.ret:
	ret								; return (error_value)

