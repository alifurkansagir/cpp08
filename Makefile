EXERCISES = ex00 ex01 ex02

all clean fclean test:
	@set -e; for exercise in $(EXERCISES); do $(MAKE) -C $$exercise $@; done

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re test
