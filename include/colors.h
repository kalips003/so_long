/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:19:41 by kmendes-          #+#    #+#             */
/*   Updated: 2024/05/15 21:30:31 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define ERR "\033[0;31mError - \e[0m"
# define ERRM "\033[0;32mError - \e[0m"
# define ERR1 "\033[0;33mError - \e[0m"

# define CLEAR "\e[2J\e[H"
# define CLS "\e[2J\e[H"
# define REVERSE "\e[7m"
# define BLINK "\e[5m"
# define R_BLINK "\e[25m"

# define RESET "\e[0m"
# define END "\e[0m\n"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define COLOR_0R_0G_0B "\033[38;5;16m"
# define COLOR_0R_0G_1B "\033[38;5;17m"
# define COLOR_0R_0G_2B "\033[38;5;18m"
# define COLOR_0R_0G_3B "\033[38;5;19m"
# define COLOR_0R_0G_4B "\033[38;5;20m"
# define COLOR_0R_0G_5B "\033[38;5;21m"
# define COLOR_0R_1G_0B "\033[38;5;22m"
# define COLOR_0R_1G_1B "\033[38;5;23m"
# define COLOR_0R_1G_2B "\033[38;5;24m"
# define COLOR_0R_1G_3B "\033[38;5;25m"
# define COLOR_0R_1G_4B "\033[38;5;26m"
# define COLOR_0R_1G_5B "\033[38;5;27m"
# define COLOR_0R_2G_0B "\033[38;5;28m"
# define COLOR_0R_2G_1B "\033[38;5;29m"
# define COLOR_0R_2G_2B "\033[38;5;30m"
# define COLOR_0R_2G_3B "\033[38;5;31m"
# define COLOR_0R_2G_4B "\033[38;5;32m"
# define COLOR_0R_2G_5B "\033[38;5;33m"
# define COLOR_0R_3G_0B "\033[38;5;34m"
# define COLOR_0R_3G_1B "\033[38;5;35m"
# define COLOR_0R_3G_2B "\033[38;5;36m"
# define COLOR_0R_3G_3B "\033[38;5;37m"
# define COLOR_0R_3G_4B "\033[38;5;38m"
# define COLOR_0R_3G_5B "\033[38;5;39m"
# define COLOR_0R_4G_0B "\033[38;5;40m"
# define COLOR_0R_4G_1B "\033[38;5;41m"
# define COLOR_0R_4G_2B "\033[38;5;42m"
# define COLOR_0R_4G_3B "\033[38;5;43m"
# define COLOR_0R_4G_4B "\033[38;5;44m"
# define COLOR_0R_4G_5B "\033[38;5;45m"
# define COLOR_0R_5G_0B "\033[38;5;46m"
# define COLOR_0R_5G_1B "\033[38;5;47m"
# define COLOR_0R_5G_2B "\033[38;5;48m"
# define COLOR_0R_5G_3B "\033[38;5;49m"
# define COLOR_0R_5G_4B "\033[38;5;50m"
# define COLOR_0R_5G_5B "\033[38;5;51m"
# define COLOR_1R_0G_0B "\033[38;5;52m"
# define COLOR_1R_0G_1B "\033[38;5;53m"
# define COLOR_1R_0G_2B "\033[38;5;54m"
# define COLOR_1R_0G_3B "\033[38;5;55m"
# define COLOR_1R_0G_4B "\033[38;5;56m"
# define COLOR_1R_0G_5B "\033[38;5;57m"
# define COLOR_1R_1G_0B "\033[38;5;58m"
# define COLOR_1R_1G_1B "\033[38;5;59m"
# define COLOR_1R_1G_2B "\033[38;5;60m"
# define COLOR_1R_1G_3B "\033[38;5;61m"
# define COLOR_1R_1G_4B "\033[38;5;62m"
# define COLOR_1R_1G_5B "\033[38;5;63m"
# define COLOR_1R_2G_0B "\033[38;5;64m"
# define COLOR_1R_2G_1B "\033[38;5;65m"
# define COLOR_1R_2G_2B "\033[38;5;66m"
# define COLOR_1R_2G_3B "\033[38;5;67m"
# define COLOR_1R_2G_4B "\033[38;5;68m"
# define COLOR_1R_2G_5B "\033[38;5;69m"
# define COLOR_1R_3G_0B "\033[38;5;70m"
# define COLOR_1R_3G_1B "\033[38;5;71m"
# define COLOR_1R_3G_2B "\033[38;5;72m"
# define COLOR_1R_3G_3B "\033[38;5;73m"
# define COLOR_1R_3G_4B "\033[38;5;74m"
# define COLOR_1R_3G_5B "\033[38;5;75m"
# define COLOR_1R_4G_0B "\033[38;5;76m"
# define COLOR_1R_4G_1B "\033[38;5;77m"
# define COLOR_1R_4G_2B "\033[38;5;78m"
# define COLOR_1R_4G_3B "\033[38;5;79m"
# define COLOR_1R_4G_4B "\033[38;5;80m"
# define COLOR_1R_4G_5B "\033[38;5;81m"
# define COLOR_1R_5G_0B "\033[38;5;82m"
# define COLOR_1R_5G_1B "\033[38;5;83m"
# define COLOR_1R_5G_2B "\033[38;5;84m"
# define COLOR_1R_5G_3B "\033[38;5;85m"
# define COLOR_1R_5G_4B "\033[38;5;86m"
# define COLOR_1R_5G_5B "\033[38;5;87m"
# define COLOR_2R_0G_0B "\033[38;5;88m"
# define COLOR_2R_0G_1B "\033[38;5;89m"
# define COLOR_2R_0G_2B "\033[38;5;90m"
# define COLOR_2R_0G_3B "\033[38;5;91m"
# define COLOR_2R_0G_4B "\033[38;5;92m"
# define COLOR_2R_0G_5B "\033[38;5;93m"
# define COLOR_2R_1G_0B "\033[38;5;94m"
# define COLOR_2R_1G_1B "\033[38;5;95m"
# define COLOR_2R_1G_2B "\033[38;5;96m"
# define COLOR_2R_1G_3B "\033[38;5;97m"
# define COLOR_2R_1G_4B "\033[38;5;98m"
# define COLOR_2R_1G_5B "\033[38;5;99m"
# define COLOR_2R_2G_0B "\033[38;5;100m"
# define COLOR_2R_2G_1B "\033[38;5;101m"
# define COLOR_2R_2G_2B "\033[38;5;102m"
# define COLOR_2R_2G_3B "\033[38;5;103m"
# define COLOR_2R_2G_4B "\033[38;5;104m"
# define COLOR_2R_2G_5B "\033[38;5;105m"
# define COLOR_2R_3G_0B "\033[38;5;106m"
# define COLOR_2R_3G_1B "\033[38;5;107m"
# define COLOR_2R_3G_2B "\033[38;5;108m"
# define COLOR_2R_3G_3B "\033[38;5;109m"
# define COLOR_2R_3G_4B "\033[38;5;110m"
# define COLOR_2R_3G_5B "\033[38;5;111m"
# define COLOR_2R_4G_0B "\033[38;5;112m"
# define COLOR_2R_4G_1B "\033[38;5;113m"
# define COLOR_2R_4G_2B "\033[38;5;114m"
# define COLOR_2R_4G_3B "\033[38;5;115m"
# define COLOR_2R_4G_4B "\033[38;5;116m"
# define COLOR_2R_4G_5B "\033[38;5;117m"
# define COLOR_2R_5G_0B "\033[38;5;118m"
# define COLOR_2R_5G_1B "\033[38;5;119m"
# define COLOR_2R_5G_2B "\033[38;5;120m"
# define COLOR_2R_5G_3B "\033[38;5;121m"
# define COLOR_2R_5G_4B "\033[38;5;122m"
# define COLOR_2R_5G_5B "\033[38;5;123m"
# define COLOR_3R_0G_0B "\033[38;5;124m"
# define COLOR_3R_0G_1B "\033[38;5;125m"
# define COLOR_3R_0G_2B "\033[38;5;126m"
# define COLOR_3R_0G_3B "\033[38;5;127m"
# define COLOR_3R_0G_4B "\033[38;5;128m"
# define COLOR_3R_0G_5B "\033[38;5;129m"
# define COLOR_3R_1G_0B "\033[38;5;130m"
# define COLOR_3R_1G_1B "\033[38;5;131m"
# define COLOR_3R_1G_2B "\033[38;5;132m"
# define COLOR_3R_1G_3B "\033[38;5;133m"
# define COLOR_3R_1G_4B "\033[38;5;134m"
# define COLOR_3R_1G_5B "\033[38;5;135m"
# define COLOR_3R_2G_0B "\033[38;5;136m"
# define COLOR_3R_2G_1B "\033[38;5;137m"
# define COLOR_3R_2G_2B "\033[38;5;138m"
# define COLOR_3R_2G_3B "\033[38;5;139m"
# define COLOR_3R_2G_4B "\033[38;5;140m"
# define COLOR_3R_2G_5B "\033[38;5;141m"
# define COLOR_3R_3G_0B "\033[38;5;142m"
# define COLOR_3R_3G_1B "\033[38;5;143m"
# define COLOR_3R_3G_2B "\033[38;5;144m"
# define COLOR_3R_3G_3B "\033[38;5;145m"
# define COLOR_3R_3G_4B "\033[38;5;146m"
# define COLOR_3R_3G_5B "\033[38;5;147m"
# define COLOR_3R_4G_0B "\033[38;5;148m"
# define COLOR_3R_4G_1B "\033[38;5;149m"
# define COLOR_3R_4G_2B "\033[38;5;150m"
# define COLOR_3R_4G_3B "\033[38;5;151m"
# define COLOR_3R_4G_4B "\033[38;5;152m"
# define COLOR_3R_4G_5B "\033[38;5;153m"
# define COLOR_3R_5G_0B "\033[38;5;154m"
# define COLOR_3R_5G_1B "\033[38;5;155m"
# define COLOR_3R_5G_2B "\033[38;5;156m"
# define COLOR_3R_5G_3B "\033[38;5;157m"
# define COLOR_3R_5G_4B "\033[38;5;158m"
# define COLOR_3R_5G_5B "\033[38;5;159m"
# define COLOR_4R_0G_0B "\033[38;5;160m"
# define COLOR_4R_0G_1B "\033[38;5;161m"
# define COLOR_4R_0G_2B "\033[38;5;162m"
# define COLOR_4R_0G_3B "\033[38;5;163m"
# define COLOR_4R_0G_4B "\033[38;5;164m"
# define COLOR_4R_0G_5B "\033[38;5;165m"
# define COLOR_4R_1G_0B "\033[38;5;166m"
# define COLOR_4R_1G_1B "\033[38;5;167m"
# define COLOR_4R_1G_2B "\033[38;5;168m"
# define COLOR_4R_1G_3B "\033[38;5;169m"
# define COLOR_4R_1G_4B "\033[38;5;170m"
# define COLOR_4R_1G_5B "\033[38;5;171m"
# define COLOR_4R_2G_0B "\033[38;5;172m"
# define COLOR_4R_2G_1B "\033[38;5;173m"
# define COLOR_4R_2G_2B "\033[38;5;174m"
# define COLOR_4R_2G_3B "\033[38;5;175m"
# define COLOR_4R_2G_4B "\033[38;5;176m"
# define COLOR_4R_2G_5B "\033[38;5;177m"
# define COLOR_4R_3G_0B "\033[38;5;178m"
# define COLOR_4R_3G_1B "\033[38;5;179m"
# define COLOR_4R_3G_2B "\033[38;5;180m"
# define COLOR_4R_3G_3B "\033[38;5;181m"
# define COLOR_4R_3G_4B "\033[38;5;182m"
# define COLOR_4R_3G_5B "\033[38;5;183m"
# define COLOR_4R_4G_0B "\033[38;5;184m"
# define COLOR_4R_4G_1B "\033[38;5;185m"
# define COLOR_4R_4G_2B "\033[38;5;186m"
# define COLOR_4R_4G_3B "\033[38;5;187m"
# define COLOR_4R_4G_4B "\033[38;5;188m"
# define COLOR_4R_4G_5B "\033[38;5;189m"
# define COLOR_4R_5G_0B "\033[38;5;190m"
# define COLOR_4R_5G_1B "\033[38;5;191m"
# define COLOR_4R_5G_2B "\033[38;5;192m"
# define COLOR_4R_5G_3B "\033[38;5;193m"
# define COLOR_4R_5G_4B "\033[38;5;194m"
# define COLOR_4R_5G_5B "\033[38;5;195m"
# define COLOR_5R_0G_0B "\033[38;5;196m"
# define COLOR_5R_0G_1B "\033[38;5;197m"
# define COLOR_5R_0G_2B "\033[38;5;198m"
# define COLOR_5R_0G_3B "\033[38;5;199m"
# define COLOR_5R_0G_4B "\033[38;5;200m"
# define COLOR_5R_0G_5B "\033[38;5;201m"
# define COLOR_5R_1G_0B "\033[38;5;202m"
# define COLOR_5R_1G_1B "\033[38;5;203m"
# define COLOR_5R_1G_2B "\033[38;5;204m"
# define COLOR_5R_1G_3B "\033[38;5;205m"
# define COLOR_5R_1G_4B "\033[38;5;206m"
# define COLOR_5R_1G_5B "\033[38;5;207m"
# define COLOR_5R_2G_0B "\033[38;5;208m"
# define COLOR_5R_2G_1B "\033[38;5;209m"
# define COLOR_5R_2G_2B "\033[38;5;210m"
# define COLOR_5R_2G_3B "\033[38;5;211m"
# define COLOR_5R_2G_4B "\033[38;5;212m"
# define COLOR_5R_2G_5B "\033[38;5;213m"
# define COLOR_5R_3G_0B "\033[38;5;214m"
# define COLOR_5R_3G_1B "\033[38;5;215m"
# define COLOR_5R_3G_2B "\033[38;5;216m"
# define COLOR_5R_3G_3B "\033[38;5;217m"
# define COLOR_5R_3G_4B "\033[38;5;218m"
# define COLOR_5R_3G_5B "\033[38;5;219m"
# define COLOR_5R_4G_0B "\033[38;5;220m"
# define COLOR_5R_4G_1B "\033[38;5;221m"
# define COLOR_5R_4G_2B "\033[38;5;222m"
# define COLOR_5R_4G_3B "\033[38;5;223m"
# define COLOR_5R_4G_4B "\033[38;5;224m"
# define COLOR_5R_4G_5B "\033[38;5;225m"
# define COLOR_5R_5G_0B "\033[38;5;226m"
# define COLOR_5R_5G_1B "\033[38;5;227m"
# define COLOR_5R_5G_2B "\033[38;5;228m"
# define COLOR_5R_5G_3B "\033[38;5;229m"
# define COLOR_5R_5G_4B "\033[38;5;230m"
# define COLOR_5R_5G_5B "\033[38;5;231m"

/*
\e = \x1B = \033 = ^[[ = ascii 27

\x[00-ff] write caracter hexa
\[000-377] OCTAL

\e[arg1;arg2;arg3m
COMBINAISONS: BOLD_BLACK "\033[30;1m"

    [nA - Move cursor up n line.
    [nB - Move cursor down n line.
    [nC - Move cursor forward (right) n column.
    [nD - Move cursor backward (left) n column.

    [E - Move cursor to the beginning of the next line.
    [F - Move cursor to the beginning of the previous line.
    [nG - Move cursor to specified column in the current row.
    [n;mH - Move cursor to the specified position (row and column). [H moves to home
    [J - Clear part of the screen.
        [0J clears from the cursor position to the end of the screen.
        [1J clears from the beginning of the screen to the cursor position.
        [2J clears the entire screen.
    [K - Clear part of the current line.
        [0K clears from the cursor position to the end of the line.
        [1K clears from the beginning of the line to the cursor position.
        [2K clears the entire line.

    [0m: Reset all text formatting (color, style, etc.) to default.
        [1m: Bold or increased intensity.
        [2m: Faint or decreased intensity.
        [3m: Italicized text (not widely supported).
        [4m: Underlined text.
        [5m: Blinking text (not widely supported).
        [7m: Inverted colors (swap foreground and background).
            [8m: Hidden text (not displayed, but still occupies space).
            [9m: Crossed-out or strikethrough text.
                [21m: Reset double underline.
                [22m: Reset bold/bright and dim text to default intensity.
                [24m: Reset underlined text.
                [25m: Reset blinking text.

[0] black [1] red [2] green [3] yellow [4] blue [5] magenta [6] cyan [7] white) [8] default

"\033[38;5;{foreground_color_code};48;5;{background_color_code}m
    [3(0-8)m: Foreground color [0;3(0-8)m (0; is  the  reset 0)
    [4(0-8)m: Background color [0;4(0-8)m

    [0;38;<n>m: ANSI color codes (0-7) foreground      = [0;38;0;<n>m
    [0;38;<n>m:         Background
    [38;2;<r>;<g>;<b>m: Truecolor foreground (RGB).
    [48;2;<r>;<g>;<b>m:
    [38;5;<n>m: 256-color foreground (0-255).
    [48;5;<n>m:


    [6n > \e[<row>;<column>R
        is often used to request the cursor position information. When the terminal receives this sequence,
        it typically responds with another sequence containing the current cursor position
    \e[s: Save current cursor position.
        \e[u: Restore cursor position saved with \e[s
    [?25l Hides the cursor.
        [?25h Shows the cursor again.
    [?1049h": Save cursor and screen state (alternative buffer).
        [?1049l": Restore cursor and screen state (main buffer).
    [?2004h": Enable bracketed paste mode (allows the terminal to distinguish pasted text from typed text).
        [?2004l": Disable bracketed paste mode.

*/

#endif //COLORS_H

// result=`ls`
// echo -e $result
// echo -e "\033[8m"

    // // Use system to execute the Bash command
    // int result = system(bashCommand = "ls -l");

/*
The color range of a 256 color terminal consists of 4 parts, often 5, in which case you actually get 258 colors:
Color numbers 0 to 7 are the default terminal colors, the actual RGB value of which is not standardized and can often be configured.
Color numbers 8 to 15 are the "bright" colors. Most of the time these are a lighter shade of the color with index - 8. They are also not standardized and can often be configured. Depending on terminal and shell, they are often used instead of or in conjunction with bold font faces.
Color numbers 16 to 231 are RGB colors. These 216 colors are defined by 6 values on each of the three RGB axes. That is, instead of values 0 - 255, each color only ranges from 0 - 5.
The color number is then calculated like this:
number = 16 + 36 * r + 6 * g + b
with r, g and b in the range 0 - 5.
The color numbers 232 to 255 are grayscale with 24 shades of gray from dark to light.
The default colors for foreground and background. In many terminals they can be configured independently from the 256 indexed colors, giving an additional two configurable colors . You get them when not setting any other color or disabling other colors (i.e. print '\e[m').
*/
