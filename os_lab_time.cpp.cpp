 #include <sys/types.h>  // для описания time_t- целое число в сек, для арифметических операций со временем
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
extern char* tzname[];
extern long timezone;
main()
{
    time_t now;

    //struct tm содержит 9 целых значений-секунды после минуты, минуты после часа, часы с 12ночи, день месяца
    // с января, год с 1900г, дни с воскресенья, дни с 1 января, флаг перехода на зимнее/летнее время
    struct tm* sp;


    //TZ  Если эта переменная установлена, то её значение имеет приоритет над настроенным системным часовым поясом.
    //изменяет или добавляет переменные окружающей среды     int  putenv ( char * строка ) переменная=значение
    // перемен. среды, например PATH, HOME и проч
    if(putenv("TZ=PST8PDT")){
        perror("Not enough memory for env \n");
     }
    (void)time(&now);  //возвращает  время в секундах с 1/01/70г в now, при неудаче возвр -1 и в errno причина ошибки 
    printf("%s", ctime(&now));  //возвращает адрес начала символьной строки


    //localtime сначала вызывает tzset, чтобы получить значение shell TZ. И на основании этого tzset инициализирует массив
    // указателей на строки tzname и внеш.переменные timezone, altzone.(переключение на основе time.daylight)
    //В timezone разница между временем UTC и данной временной зоной.
    //
    sp = localtime(&now);   //возвращают адрес структуры tm. 
     if(sp == NULL) {
        perror ("Can`t print data \n");
     }



    printf("%d/%d/%02d %d:%02d %s\n",
        sp->tm_mon + 1, sp->tm_mday,
        sp->tm_year, sp->tm_hour,
        sp->tm_min, tzname[sp->tm_isdst]);
    exit(0);
}