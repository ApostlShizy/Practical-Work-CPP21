1. Ведомость учёта
Что нужно сделать
Вы уже создавали программу чтения и записи ведомости. Теперь её нужно обобщить и дополнить использованием структур.

Формат ведомости прежний:

сначала — имя и фамилия получателя денег;
далее — дата выдачи в формате ДД.ММ.ГГГГ;
затем — сумма выплаты в рублях.
Данные разделяются пробелами. В конце каждой записи должен быть перевод строки. Структура данных должна соответствовать этому формату.

При старте программы пользователь отправляет команду: list или add. Команда list осуществляет чтение из файла ведомости, как и прежде, только уже в структуре данных, и отображает их на экране.

Команда add добавляет новую запись в конец ведомости.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

2. Модель данных для посёлка
Что нужно сделать
Используя структуры данных, создайте подробную модель посёлка.

Что известно:

Посёлок состоит из участков, у каждого участка свой номер.
На любом участке может стоять жилой дом, а также другие сооружения: 
гараж, 
сарай (бытовка),
баня. 
Дана информация о площади, которую каждое здание занимает на участке.
В доме может быть 1–3 этажа, на этаже — 2–4 комнаты:
спальня,
кухня,
ванная,
детская,
гостиная.
Дана информация о количестве комнат и высоте потолка на каждом этаже.
Дана информация о площади, которую занимает каждая комната.
В доме и бане может быть печь с трубой.
Для всех упомянутых сущностей нужно объявить структуры данных.

Обязательно для выполнения задания
Опишите структуры данных для создания модели посёлка. Структуры должны быть:

связными и легко расширяемыми,
без дублирующих конструкций.
Реализуйте заполнение структур данных.

Пользователь заполняет данные о посёлке: вводит общее количество участков, а потом детализирует каждый.

Сначала указывается количество построек на участке, а затем — информация, какие это постройки, сколько этажей в доме, какие комнаты на этажах.

После ввода данных можно рассчитать суммарный параметр, например процент земли, занимаемой постройками, от общей площади посёлка. Главное в этой задаче не операция подсчёта, а структуры данных.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

3. Математический вектор
Что нужно сделать
Реализуйте структуру двумерного математического вектора и основные операции над ним. Обе координаты вектора (x и y) должны быть вещественными числами.

Начиная работу с программой, пользователь вводит команду. Затем в зависимости от команды пользователь вводит аргументы. Это могут быть как векторы, так и обычные скалярные значения. Результат помещается в стандартный вывод. Это тоже может быть или вектор, или скаляр.

Реализуйте в виде отдельных функций операции:

сложение двух векторов — команда add;
вычитание двух векторов — команда subtract;
умножение вектора на скаляр — команда scale;
нахождение длины вектора — команда length;
нормализация вектора — команда normalize.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

4. Пошаговая ролевая игра (дополнительная задача)
Что нужно сделать
Реализуйте упрощённую версию пошаговой ролевой игры.

Действие разворачивается на карте размером 20 на 20 клеток. По клеткам перемещаются игрок и его противники.

После каждого хода игрока карта показывается вновь со всеми противниками на ней:

игрок помечается буквой P; 
противники — буквой E;
пустые места — точкой.
Каждый персонаж игры представлен в виде структуры с полями: 

«Имя»;
«Жизни»;
«Броня»;
«Урон».
Сначала создаётся пять противников в случайных клетках карты:

Имена противникам задаются в формате Enemy #N, где N — порядковый номер. 
Уровень жизни противников задаётся случайно — от 50 до 150. 
Уровень брони варьируется от 0 до 50. 
Урон тоже выбирается случайно — от 15 до 30.
Игрок конструирует своего персонажа самостоятельно. Задаёт все его параметры, включая имя. Все персонажи появляются в случайных местах карты.

Игрок ходит с помощью команд: L, R, U, D (по первым буквам слов left, right, up, down). В зависимости от команды выбирается направление перемещения: влево, вправо, вверх, вниз.

Противники перемещаются в случайном направлении.

Если игрок перемещается в сторону, где уже кто-то находится, он наносит этому персонажу урон. Противники при этом никогда не бьют друг друга: они просто пропускают ход и остаются на своём месте. За пределы карты (20 на 20 клеток) ходить нельзя никому. Если кто-то выбрал направление за границами, ход пропускается.

Формула расчёта урона совпадает с той, что была в материале. Жизни уменьшаются на размер урона. При этом броня тоже сокращается на приведённый урон.

Игра заканчивается, когда умирают либо все противники, либо игрок. В первом случае на экран выводится сообщение о победе, во втором — о поражении.

Если в начале хода игрок вводит команду save или load вместо направления перемещения, то игра либо сохраняет своё состояние в файл, либо загружает это состояние из файла.
