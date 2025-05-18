.data
.eqv SYS_PRINT_INT    1
.eqv SYS_PRINT_STRING 4
.eqv SYS_READ_INT     5
.eqv SYS_READ_STRING  8
.eqv SYS_EXIT         10
.eqv SYS_PRINT_CHAR   11
.eqv SYS_READ_CHAR    12

.eqv char_0     48
.eqv char_1     49
.eqv char_2     50
.eqv char_3     51
.eqv char_4     52
.eqv char_5     53
.eqv char_6     54
.eqv char_N     78
.eqv char_Q     81
.eqv char_R     82
.eqv char_Y     89
.eqv char_n     110
.eqv char_q     113
.eqv char_r     114
.eqv char_y     121
.eqv char_space 32

.eqv player_a_turn 0
.eqv player_b_turn 1
.eqv number_of_ships 6
.eqv number_of_cells 49
.eqv input_coordinates_length_shot 4
.eqv input_coordinates_length_ship 8

player_a_map: .byte 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0

player_b_map: .byte 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0

grid_size:        .word  7
ship_coordinates: .space 8
shot_coordinates: .space 5

title_0:  .asciiz "===============================================================================================================\n"
title_1:  .asciiz "||    ______        _     _________  _________  _____     ________   ______   ____  ____  _____  _______     ||\n"
title_2:  .asciiz "||   |_   _  \\     / \\   |  _   _  ||  _   _  ||_   _|   |_   __  | / ____ \\ |_   ||   _||_   _||_   __  \\   ||\n"
title_3:  .asciiz "||     | |_) |    / _ \\  |_/ | | \\_||_/ | | \\_|  | |       | |_ \\_|| (___ \\_|  | |__| |    | |    | |__) |   ||\n"
title_4:  .asciiz "||     |  __ \\   / ___ \\     | |        | |      | |   _   |  _| _  _.____`.   |  __  |    | |    |  ___/    ||\n"
title_5:  .asciiz "||    _| |__) |_/ /   \\ \\_  _| |_      _| |_    _| |__/ | _| |__/ || \\____) | _| |  | |_  _| |_  _| |_       ||\n"
title_6:  .asciiz "||   |_______/|____| |____||_____|    |_____|  |________||________| \\______/ |____||____||_____||_____|      ||\n"
title_7:  .asciiz "||                                                                                                           ||\n"
title_8:  .asciiz "                                                                                               __/___\n"
title_9:  .asciiz "                                                                                         _____/______|\n"
title_10: .asciiz "                                                                                 _______/_____\\_______\\_____\n"
title_11: .asciiz "                                                                                 \\              < < <       |\n"
title_12: .asciiz "                                                                               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"

rule_0:     .asciiz "   ________________________________\n"
rule_1:     .asciiz "   |    ___  __  ____   ________  |\n"
rule_2:     .asciiz "   |   / _ \\/ / / / /  / __/ __/  |\n"
rule_3:     .asciiz "   |  / , _/ /_/ / /__/ _/_\\ \\    |\n"
rule_4:     .asciiz "   | /_/|_|\\____/____/___/___/    |\n"
rule_5:     .asciiz "   |______________________________|\n"
rule_6:     .asciiz "\nSetup Phase:\n"
rule_7:     .asciiz "    Players take turns placing their ships on a 7x7 grid. Placing format: (r_bow  c_bow  r_stern  c_stern)\n"
rule_8:     .asciiz "    Each player has:\n"
rule_9:     .asciiz "        3 ships of size 2x1\n"
rule_10:    .asciiz "        2 ships of size 3x1\n"
rule_11:    .asciiz "        1 ship of size 4x1\n"
rule_12:    .asciiz "    Ships cannot overlap.\n"
rule_13:    .asciiz "    Ships cannot be placed diagonally.\n\n"

rule_14:    .asciiz "Gameplay:\n"
rule_15:    .asciiz "    Players alternate turns.\n"
rule_16:    .asciiz "    On their turn, a player inputs coordinates (r  c) to target an opponent's cell.\n"
rule_17:    .asciiz "    Hit Announcement:\n"
rule_18:    .asciiz "        If a targeted cell is part of an opponent's ship, an announcement appears: HIT!\n\n"

rule_19:    .asciiz "Update Board:\n"
rule_20:    .asciiz "    A hit cell's value changes to 0, indicating damage.\n"
rule_21:    .asciiz "    A ship is destroyed when all its cells are hit.\n\n"

rule_22:    .asciiz "Winning:\n"
rule_23:    .asciiz "    The game ends when a player's board has no remaining ships.\n"
rule_24:    .asciiz "    The first player to lose all their ships is the loser.\n"

proceed:  .asciiz "\n   PROCEED ? [Y/N]: "
start:    .asciiz "\n   START ? [Y/N]: "

char_A:        .asciiz "A"
char_B:        .asciiz "B"
player_label:  .asciiz "    |         Player A          |        |          Player B         | \n"
grid_bar:      .asciiz "    o---o---o---o---o---o---o---o        o---o---o---o---o---o---o---o \n"
grid_horiz:    .asciiz "    |---+---+---+---+---+---+---|        |---+---+---+---+---+---+---| \n"
grid_helper:   .asciiz "    | "
grid_vert:     .asciiz        " | "
grid_trans:    .asciiz                                   "       | "

space: .asciiz " "
endl:  .asciiz "\n"
comma: .asciiz ","

player_a_place_turn: .asciiz "\n!!! PLAYER A TURN !!!\n"
player_b_place_turn: .asciiz "\n!!! PLAYER B TURN !!!\n"

prompt_ship: .asciiz "\n! ENTER SHIPS LOCATIONS !~\nInput format: [r_bow  c_bow  r_stern  c_stern]\n[Q]: Quit to main menu\n[R]: Restart\n"
prompt_shot: .asciiz "Enter shot location\nInput format: [r  c]\n[Q]: Quit to main menu\n[R]: Restart\n"

invalid_format:    .asciiz "\nInvalid coordinates format. Try again.\n"
invalid_size:      .asciiz "\nInvalid ship size. Try again.\n"
invalid_location:  .asciiz "\nShips cannot overlap. Try again.\n"
invalid_placement: .asciiz "\nShips cannot be placed diagonally. Try again.\n"
invalid_shot:      .asciiz "\nInvalid shot coordinates. Try again.\n"

confirmed_ship:    .asciiz "\nShip position confirmed.\n"

hit:         .asciiz "\n O_O HIT! O_O \n"
miss:        .asciiz "\n T.T MISS! T.T \n"

a_wins:      .asciiz "\n!!! PLAYER A WON THE GAME. CONGRATULATIONS !!!\n"
b_wins:      .asciiz "\n!!! PLAYER B WON THE GAME. CONGRATULATIONS !!!\n"

.text
main:
    lw $s0 grid_size
    la $s4 player_a_map
    la $s5 player_b_map
    li $s7 player_a_turn

    jal game_menu
    jal rules_screen
    jal print_maps

    li $s1 1
    li $s2 2
    li $s3 3
    la $a0 player_a_place_turn
    li $v0 SYS_PRINT_STRING
    syscall
    jal read_ship
    jal print_maps

    li $s7 player_b_turn
    li $s1 1
    li $s2 2
    li $s3 3
    la $a0 player_b_place_turn
    li $v0 SYS_PRINT_STRING
    syscall
    jal read_ship
    jal print_maps

    li $s7 player_a_turn
    jal read_shot
    jal print_maps

exit:
    li $v0 SYS_EXIT
    syscall

game_menu:
    # region[rgba(0, 255, 0, 0.1)]
    la $a0 title_0
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_1
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_2
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_3
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_4
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_5
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_6
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_7
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_0
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_8
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_9
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_10
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_11
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 title_12
    li $v0 SYS_PRINT_STRING
    syscall

    start_loop:
        la $a0 start
        li $v0 SYS_PRINT_STRING
        syscall
        li $v0 SYS_READ_CHAR
        syscall

        move $t0 $v0
        # read '\n' character
        li $v0 SYS_READ_CHAR
        syscall

        la $a0 endl
        li $v0 SYS_PRINT_STRING
        syscall
        la $a0 endl
        li $v0 SYS_PRINT_STRING
        syscall

        beq $t0 char_y game_menu_proceed
        beq $t0 char_Y game_menu_proceed
        beq $t0 char_n exit
        beq $t0 char_N exit
        
        j start_loop

    game_menu_proceed:
        jr $ra
    # endregion

rules_screen:
    # region[rgba(0, 0, 255, 0.1)]
    la $a0 rule_0
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_1
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_2
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_3
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_4
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_5
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_6
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_7
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_8
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_9
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_10
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_11
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_12
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_13
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_14
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_15
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_16
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_17
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_18
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_19
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_20
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_21
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_22
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_23
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 rule_24
    li $v0 SYS_PRINT_STRING
    syscall

    proceed_loop:
        la $a0 proceed
        li $v0 SYS_PRINT_STRING
        syscall
        li $v0 SYS_READ_CHAR
        syscall

        move $t0 $v0
        # read '\n' character
        li $v0 SYS_READ_CHAR
        syscall

        la $a0 endl
        li $v0 SYS_PRINT_STRING
        syscall
        la $a0 endl
        li $v0 SYS_PRINT_STRING
        syscall

        beq $t0 char_y rules_screen_proceed
        beq $t0 char_Y rules_screen_proceed
        beq $t0 char_n main
        beq $t0 char_N main
        j proceed_loop
    
    rules_screen_proceed:
        jr $ra
    # endregion

read_ship:
    # region[rgba(255, 0, 0, 0.2)]
    la $a0 prompt_ship
    li $v0 SYS_PRINT_STRING
    syscall

    li $t0 1
    read_ship_loop:
        or $t0 $s1 $s2
        or $t0 $t0 $s3
        beq $t0 $0 read_ship_loop_end

        la $a0 ship_coordinates
        li $a1 input_coordinates_length_ship
        li $v0 SYS_READ_STRING
        syscall

        #===== VALIDATING INPUT =====#
        user_option_checking:
            lb $t1 ship_coordinates
            beq $t1 char_R read_ship
            beq $t1 char_r read_ship
            beq $t1 char_Q main
            beq $t1 char_q main

        format_checking:
            li $t1 1
            lb $t2 ship_coordinates($t1)
            bne $t2 char_space invalid_syntax
            li $t1 3
            lb $t2 ship_coordinates($t1)
            bne $t2 char_space invalid_syntax
            li $t1 5
            lb $t2 ship_coordinates($t1)
            bne $t2 char_space invalid_syntax

        value_checking:
            li $t1 0
            lb $t2 ship_coordinates($t1)
            blt $t2 char_0 invalid_syntax
            bgt $t2 char_6 invalid_syntax
            li $t1 2
            lb $t3 ship_coordinates($t1)
            blt $t3 char_0 invalid_syntax
            bgt $t3 char_6 invalid_syntax
            li $t1 4
            lb $t4 ship_coordinates($t1)
            blt $t4 char_0 invalid_syntax
            bgt $t4 char_6 invalid_syntax
            li $t1 6
            lb $t5 ship_coordinates($t1)
            blt $t5 char_0 invalid_syntax
            bgt $t5 char_6 invalid_syntax

        diagonal_checking:
            beq $t2 $t4 horizontal_size_checking
            beq $t3 $t5 vertical_size_checking
            j diagonally_placed

        horizontal_size_checking:   
            sub $s6 $t5 $t3
            abs $s6 $s6
            addi $s6 $s6 1
            blt $s6 2 invalid_ship_size
            bgt $s6 4 invalid_ship_size

            beq $s6 2 horizontal_sub_size_2
            beq $s6 3 horizontal_sub_size_3
            beq $s6 4 horizontal_sub_size_4

            horizontal_sub_size_2:
                beq $s3 $0 invalid_ship_size
                j overlap_checking
            
            horizontal_sub_size_3:
                beq $s2 $0 invalid_ship_size
                j overlap_checking
            
            horizontal_sub_size_4:
                beq $s1 $0 invalid_ship_size
                j overlap_checking

        vertical_size_checking:
            sub $s6 $t4 $t2
            abs $s6 $s6
            addi $s6 $s6 1
            blt $s6 2 invalid_ship_size
            bgt $s6 4 invalid_ship_size

            beq $s6 2 vertical_sub_size_2
            beq $s6 3 vertical_sub_size_3
            beq $s6 4 vertical_sub_size_4

            vertical_sub_size_2:
                beq $s3 $0 invalid_ship_size
                j overlap_checking
            
            vertical_sub_size_3:
                beq $s2 $0 invalid_ship_size
                j overlap_checking
            
            vertical_sub_size_4:
                beq $s1 $0 invalid_ship_size
                j overlap_checking

        overlap_checking:
            li $t1 0
            lb $t2 ship_coordinates($t1)
            li $t1 2
            lb $t3 ship_coordinates($t1)
            li $t1 4
            lb $t4 ship_coordinates($t1)
            li $t1 6
            lb $t5 ship_coordinates($t1)

            addi $t2 $t2 -48
            addi $t3 $t3 -48
            addi $t4 $t4 -48
            addi $t5 $t5 -48

            beq $s7 player_b_turn b_check
            beq $t2 $t4 horiz_a_check
            beq $t3 $t5 vert_a_check

            vert_a_check:
                blt $t2 $t4 vert_a_check_continue
                # swap if t2 > t4
                xor $t2 $t2 $t4
                xor $t4 $t4 $t2
                xor $t2 $t2 $t4

            vert_a_check_continue:
                mul $t6 $t2 7
                add $t6 $t6 $t3

            vert_a_check_loop:
                lb $t7 player_a_map($t6)
                bne $t7 $0 overlapped_error
                beq $t2 $t4 overlap_checking_end
                addi $t2 $t2 1
                addi $t6 $t6 7

                j vert_a_check_loop

            horiz_a_check:
                blt $t3 $t5 horiz_a_check_continue
                # swap if t3 > t5
                xor $t3 $t3 $t5
                xor $t5 $t5 $t3
                xor $t3 $t3 $t5

                horiz_a_check_continue:
                    mul $t6 $t2 7
                    add $t6 $t6 $t3

                horiz_a_check_loop:
                    lb $t7 player_a_map($t6)
                    bne $t7 $0 overlapped_error
                    beq $t3 $t5 overlap_checking_end
                    addi $t3 $t3 1
                    addi $t6 $t6 1

                    j horiz_a_check_loop
            
            b_check:
                beq $t2 $t4 horiz_b_check
                beq $t3 $t5 vert_b_check

            vert_b_check:
                blt $t2 $t4 vert_b_check_continue
                # swap if t2 > t4
                xor $t2 $t2 $t4
                xor $t4 $t4 $t2
                xor $t2 $t2 $t4

            vert_b_check_continue:
                mul $t6 $t2 7
                add $t6 $t6 $t3

            vert_b_check_loop:
                lb $t7 player_b_map($t6)
                bne $t7 $0 overlapped_error
                beq $t2 $t4 overlap_checking_end
                addi $t2 $t2 1
                addi $t6 $t6 7

                j vert_b_check_loop

            horiz_b_check:
                blt $t3 $t5 horiz_b_check_continue
                # swap if t3 > t5
                xor $t3 $t3 $t5
                xor $t5 $t5 $t3
                xor $t3 $t3 $t5

                horiz_b_check_continue:
                    mul $t6 $t2 7
                    add $t6 $t6 $t3

                horiz_b_check_loop:
                    lb $t7 player_b_map($t6)
                    bne $t7 $0 overlapped_error
                    beq $t3 $t5 overlap_checking_end
                    addi $t3 $t3 1
                    addi $t6 $t6 1

                    j horiz_b_check_loop
        
        overlap_checking_end:
            j place_ships
        
        invalid_syntax:
            la $a0 invalid_format
            li $v0 SYS_PRINT_STRING
            syscall

            j read_ship_loop

        invalid_ship_size:
            la $a0 invalid_size
            li $v0 SYS_PRINT_STRING
            syscall

            j read_ship_loop

        diagonally_placed:
            la $a0 invalid_placement
            li $v0 SYS_PRINT_STRING
            syscall

            j read_ship_loop

        overlapped_error:
            la $a0 invalid_location
            li $v0 SYS_PRINT_STRING
            syscall

            j read_ship_loop

        #==== END VALIDATING INPUT ====#

        #===== PLACING SHIP =====#
    place_ships:
        la $a0 confirmed_ship
        li $v0 SYS_PRINT_STRING
        syscall

        li $t1 0
        lb $t2 ship_coordinates($t1)
        li $t1 2
        lb $t3 ship_coordinates($t1)
        li $t1 4
        lb $t4 ship_coordinates($t1)
        li $t1 6
        lb $t5 ship_coordinates($t1)

        addi $t2 $t2 -48
        addi $t3 $t3 -48
        addi $t4 $t4 -48
        addi $t5 $t5 -48

        beq $s6 2 place_ships_sub_size_2
        beq $s6 3 place_ships_sub_size_3
        beq $s6 4 place_ships_sub_size_4

        place_ships_sub_size_2:
            addi $s3 $s3 -1
            j place_ships_continue
        
        place_ships_sub_size_3:
            addi $s2 $s2 -1
            j place_ships_continue
        
        place_ships_sub_size_4:
            addi $s1 $s1 -1
            j place_ships_continue

        place_ships_continue:
        beq $s7 player_b_turn draw_ship_a_end

        beq $t2 $t4 draw_horiz_a
        beq $t3 $t5 draw_vert_a

        draw_vert_a:
            blt $t2 $t4 draw_vert_a_continue
            # swap if t2 > t4
            xor $t2 $t2 $t4
            xor $t4 $t4 $t2
            xor $t2 $t2 $t4

            draw_vert_a_continue:
                mul $t6 $t2 7
                add $t6 $t6 $t3

            draw_vert_a_loop:
                sb $s6 player_a_map($t6)
                beq $t2 $t4 place_ships_end
                addi $t2 $t2 1
                addi $t6 $t6 7

                j draw_vert_a_loop

        draw_horiz_a:
            blt $t3 $t5 draw_horiz_a_continue
            # swap if t3 > t5
            xor $t3 $t3 $t5
            xor $t5 $t5 $t3
            xor $t3 $t3 $t5

            draw_horiz_a_continue:
                mul $t6 $t2 7
                add $t6 $t6 $t3

            draw_horiz_a_loop:
                sb $s6 player_a_map($t6)
                beq $t3 $t5 place_ships_end
                addi $t3 $t3 1
                addi $t6 $t6 1

                j draw_horiz_a_loop
        
        draw_ship_a_end:
            beq $t2 $t4 draw_horiz_b
            beq $t3 $t5 draw_vert_b

        draw_vert_b:
            blt $t2 $t4 draw_vert_b_continue
            # swap if t2 > t4
            xor $t2 $t2 $t4
            xor $t4 $t4 $t2
            xor $t2 $t2 $t4

            draw_vert_b_continue:
                mul $t6 $t2 7
                add $t6 $t6 $t3

            draw_vert_b_loop:
                sb $s6 player_b_map($t6)
                beq $t2 $t4 place_ships_end
                addi $t2 $t2 1
                addi $t6 $t6 7

                j draw_vert_b_loop

        draw_horiz_b:
            blt $t3 $t5 draw_horiz_b_continue
            # swap if t3 > t5
            xor $t3 $t3 $t5
            xor $t5 $t5 $t3
            xor $t3 $t3 $t5

            draw_horiz_b_continue:
                mul $t6 $t2 7
                add $t6 $t6 $t3

            draw_horiz_b_loop:
                sb $s6 player_b_map($t6)
                beq $t3 $t5 place_ships_end
                addi $t3 $t3 1
                addi $t6 $t6 1

                j draw_horiz_b_loop
            
        #==== END PLACING SHIP ====#
        place_ships_end:
            addi $t0 $t0 -1
            j read_ship_loop

    read_ship_loop_end:

    jr $ra
    # endregion

read_shot:
    # region[rgba(0, 255, 0, 0.2)]
    la $a0 prompt_shot
    li $v0 SYS_PRINT_STRING
    syscall

    read_shot_loop:
        beq $s7 player_a_turn prompt_a_shot
        beq $s7 player_b_turn prompt_b_shot

        prompt_a_shot:
            la $a0 player_a_place_turn
            li $v0 SYS_PRINT_STRING
            syscall
            j read_shot_continue

        prompt_b_shot:
            la $a0 player_b_place_turn
            li $v0 SYS_PRINT_STRING
            syscall
            j read_shot_continue

        read_shot_continue:

        la $a0 shot_coordinates
        li $a1 input_coordinates_length_shot
        li $v0 SYS_READ_STRING
        syscall

        #===== VALIDATING INPUT =====#
        user_option_checking_shot:
            lb $t1 shot_coordinates
            beq $t1 char_R read_shot
            beq $t1 char_r read_shot
            beq $t1 char_Q main
            beq $t1 char_q main

        format_checking_shot:
            li $t1 1
            lb $t2 shot_coordinates($t1)
            bne $t2 char_space invalid_syntax_shot

        value_checking_shot:
            li $t1 0
            lb $t2 shot_coordinates($t1)
            blt $t2 char_0 invalid_shot_coordinates
            bgt $t2 char_6 invalid_shot_coordinates
            li $t1 2
            lb $t3 shot_coordinates($t1)
            blt $t3 char_0 invalid_shot_coordinates
            bgt $t3 char_6 invalid_shot_coordinates

        j shooting

        invalid_syntax_shot:
            la $a0 invalid_format
            li $v0 SYS_PRINT_STRING
            syscall

            j read_shot_loop

        invalid_shot_coordinates:
            la $a0 invalid_shot
            li $v0 SYS_PRINT_STRING
            syscall

            j read_shot_loop

        #==== END VALIDATING INPUT ====#

        #===== SHOOTING =====#
        shooting:
            li $t1 0
            lb $t2 shot_coordinates($t1)
            li $t1 2
            lb $t3 shot_coordinates($t1)

            addi $t2 $t2 -48
            addi $t3 $t3 -48

            beq $s7 player_a_turn a_shot
            beq $s7 player_b_turn b_shot

        a_shot:
            li $s7 player_b_turn
            mul $t4 $t2 7
            add $t4 $t4 $t3

            lb $t5 player_b_map($t4)
            bne $t5 $0 a_hit
            j a_missed

        a_hit:
            la $a0 hit
            li $v0 SYS_PRINT_STRING
            syscall

            # UPDATE PLAYER B'S MAP
            sb $0 player_b_map($t4)
            j endgame_status_checking

        a_missed:
            la $a0 miss
            li $v0 SYS_PRINT_STRING
            syscall
            
            j read_shot_loop

        # B's turn
        b_shot:
            li $s7 player_a_turn
            mul $t4 $t2 7
            add $t4 $t4 $t3

            lb $t5 player_a_map($t4)
            bne $t5 $0 b_hit
            j b_missed

        b_hit:
            la $a0 hit
            li $v0 SYS_PRINT_STRING
            syscall

            # UPDATE PLAYER A'S MAP
            sb $0 player_a_map($t4)
            j endgame_status_checking

        b_missed:
            la $a0 miss
            li $v0 SYS_PRINT_STRING
            syscall
            
            j read_shot_loop

        #==== END SHOOTING ====#

        #===== STATUS CHECKING =====#
        endgame_status_checking:
            li $t0 0

            beq $s7 player_a_turn a_status_loop
            beq $s7 player_b_turn b_status_loop

            a_status_loop:
                lb $t1 player_a_map($t0)
                bne $t1 $0 continue_the_game

                addi $t0 $t0 1
                beq $t0 number_of_cells endgame_status_checking_end

                j a_status_loop

            b_status_loop:
                lb $t1 player_b_map($t0)
                bne $t1 $0 continue_the_game

                addi $t0 $t0 1
                beq $t0 number_of_cells endgame_status_checking_end

                j b_status_loop

            continue_the_game:
                j read_shot_loop

        endgame_status_checking_end:
            beq $s7 player_b_turn player_a_wins
            beq $s7 player_a_turn player_b_wins
            
        #==== END STATUS CHECKING ====#

        player_a_wins:
            la $a0 a_wins
            li $v0 SYS_PRINT_STRING
            syscall

            j read_shot_end

        player_b_wins:
            la $a0 b_wins
            li $v0 SYS_PRINT_STRING
            syscall

            j read_shot_end

    read_shot_end:
        jr $ra

print_maps:
    la $a0 grid_bar
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 player_label
    li $v0 SYS_PRINT_STRING
    syscall
    la $a0 grid_bar
    li $v0 SYS_PRINT_STRING
    syscall

    add $t2 $s4 $0
    add $t3 $s5 $0
    li $t0 0

    print_map:
        li $t1 0
        li $t4 0
        print_row_loop:
            beq $t4 $s0 print_row_loop_end

            la $a0 grid_helper
            li $v0 SYS_PRINT_STRING
            syscall

            print_row_a_loop:
                beq $t1 $s0 print_row_a_loop_end

                lb $a0 0($t2)
                li $v0 SYS_PRINT_INT
                syscall
                la $a0 grid_vert
                li $v0 SYS_PRINT_STRING
                syscall

                addi $t1 $t1 1
                addi $t2 $t2 1
                j print_row_a_loop

            print_row_a_loop_end:
                la $a0 grid_trans
                li $v0 SYS_PRINT_STRING
                syscall

            print_row_b_loop:
                beq $t1 $zero print_row_b_loop_end

                lb $a0 0($t3)
                li $v0 SYS_PRINT_INT
                syscall
                la $a0 grid_vert
                li $v0 SYS_PRINT_STRING
                syscall

                addi $t1 $t1 -1
                addi $t3 $t3 1
                j print_row_b_loop

            print_row_b_loop_end:
                beq $t4 6 print_row_loop_end
                la $a0 endl
                li $v0 SYS_PRINT_STRING
                syscall
                la $a0 grid_horiz
                li $v0 SYS_PRINT_STRING
                syscall
            
            addi $t4 $t4 1
            j print_row_loop
        
        print_row_loop_end:
            la $a0 endl
            li $v0 SYS_PRINT_STRING
            syscall
            la $a0 grid_bar
            li $v0 SYS_PRINT_STRING
            syscall
        jr $ra