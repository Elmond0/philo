# Nome dell’eseguibile
NAME		:= philo

# Directories
SRC_DIR		:= sources
OBJ_DIR		:= obj
INC_DIR		:= include

# Compiler e flags
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
CPPFLAGS	:= -I$(INC_DIR)
LDFLAGS		:=
LDLIBS		:= -pthread

# Sorgenti (tutti i .c dentro sources e sottocartelle)
SRCS		:= $(shell find $(SRC_DIR) -name "*.c")

# Oggetti (stessa struttura di cartelle sotto obj/)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Dipendenze generate automaticamente (.d)
DEPS		:= $(OBJS:.o=.d)

# Regola di default
all: $(NAME)

# Link finale
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@
	@echo -e "\033[32m$(NAME) created!\033[0m"

# Crea obj/ se non esiste
$(OBJ_DIR):
	@mkdir -p $@

# Regola pattern: compila ogni .c -> .o e genera anche .d
# -MMD -MP crea i file .d per le dipendenze degli header
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@
	@echo -e "\033[90m$< compiled\033[0m"

# Include delle dipendenze (se esistono)
-include $(DEPS)

# Pulizia oggetti
clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "\033[33mObjects removed.\033[0m"

# Pulizia completa
fclean: clean
	@rm -f $(NAME)
	@echo -e "\033[31mBinaries wiped\033[0m"

# Rebuild
re: fclean all

.PHONY: all clean fclean re
