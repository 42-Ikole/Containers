/* ************************************************************************** */
/*                                                                            */
/*      .'(     /`-.     )\.--.       .'(        )\   )\     /`-.      /`-.   */
/*  ,') \  )  ,' _  \   (   ._.'  ,') \  )      (  ',/ /   ,' _  \   ,' _  \  */
/* (  '-' (  (  '-' (    `-.`.   (  '-' (        )    (   (  '-' (  (  '-' (  */
/*  ) .-.  )  )   _  )  ,_ (  \   ) .-.  )      (  \(\ \   )   _  )  ) ,._.'  */
/* (  ,  ) \ (  ,' ) \ (  '.)  ) (  ,  ) \       `.) /  ) (  ,' ) \ (  '      */
/*  )/    )/  )/    )/  '._,_.'   )/    )/           '.(   )/    )/  )/       */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#include <linear_hash_map.hpp>

ft::prime_bs::prime_type	ft::prime_bs::primes[] = {
	37lu, 59lu, 127lu, 251lu, 397lu, 797lu, 1259lu, 
	2539lu, 4027lu, 6421lu, 8089lu, 10193lu, 12853lu, 16193lu,
	20399lu, 25717lu, 32401lu, 40823lu, 51437lu, 64811lu, 81649lu,
	102877lu, 129607lu, 163307lu, 205759lu, 259229lu, 326617lu,
	411527lu, 518509lu, 653267lu, 823117lu, 1037059lu, 1306601lu,
	1646237lu, 2074129lu, 2613229lu, 3292489lu, 4148279lu, 5226491lu,
	6584983lu, 8296553lu, 10453007lu, 13169977lu, 16593127lu, 20906033lu,
	26339969lu, 33186281lu, 41812097lu, 52679969lu, 66372617lu,
	83624237lu, 105359939lu, 132745199lu, 167248483lu, 210719881lu,
	265490441lu, 334496971lu, 421439783lu, 530980861lu, 668993977lu,
	842879579lu, 1061961721lu, 1337987929lu, 1685759167lu, 2123923447lu,
	2675975881lu, 3371518343lu, 4247846927lu, 5351951779lu, 6743036717lu,
	8495693897lu, 10703903591lu, 13486073473lu, 16991387857lu,
	21407807219lu, 26972146961lu, 33982775741lu, 42815614441lu,
	53944293929lu, 67965551447lu, 85631228929lu, 107888587883lu,
	135931102921lu, 171262457903lu, 215777175787lu, 271862205833lu,
	342524915839lu, 431554351609lu, 543724411781lu, 685049831731lu,
	863108703229lu, 1087448823553lu, 1370099663459lu, 1726217406467lu,
	2174897647073lu, 2740199326961lu, 3452434812973lu, 4349795294267lu,
	5480398654009lu, 6904869625999lu, 8699590588571lu, 10960797308051lu,
	13809739252051lu, 17399181177241lu, 21921594616111lu, 27619478504183lu,
	34798362354533lu, 43843189232363lu, 55238957008387lu, 69596724709081lu,
	87686378464759lu, 110477914016779lu, 139193449418173lu,
	175372756929481lu, 220955828033581lu, 278386898836457lu,
	350745513859007lu, 441911656067171lu, 556773797672909lu,
	701491027718027lu, 883823312134381lu, 1113547595345903lu,
	1402982055436147lu, 1767646624268779lu, 2227095190691797lu,
	2805964110872297lu, 3535293248537579lu, 4454190381383713lu,
	5611928221744609lu, 7070586497075177lu, 8908380762767489lu,
	11223856443489329lu, 14141172994150357lu, 17816761525534927lu,
	22447712886978529lu, 28282345988300791lu, 35633523051069991lu,
	44895425773957261lu, 56564691976601587lu, 71267046102139967lu,
	89790851547914507lu, 113129383953203213lu, 142534092204280003lu,
	179581703095829107lu, 226258767906406483lu, 285068184408560057lu,
	359163406191658253lu, 452517535812813007lu, 570136368817120201lu,
	718326812383316683lu, 905035071625626043lu, 1140272737634240411lu,
	1436653624766633509lu, 1810070143251252131lu, 2280545475268481167lu,
	2873307249533267101lu, 3620140286502504283lu, 4561090950536962147lu,
	5746614499066534157lu, 7240280573005008577lu, 9122181901073924329lu,
	11493228998133068689lu, 14480561146010017169lu, 18446744073709551557lu, 0
};

/*
** most compilers will generate specialized assembly for each rvalue modulo
** note that these are not inline since that will prevent the compiler from doing further optimizations
*/
static ft::prime_bs::prime_type mod37(ft::prime_bs::prime_type n) { return n % 37lu; }
static ft::prime_bs::prime_type mod59(ft::prime_bs::prime_type n) { return n % 59lu; }
static ft::prime_bs::prime_type mod127(ft::prime_bs::prime_type n) { return n % 127lu; }
static ft::prime_bs::prime_type mod251(ft::prime_bs::prime_type n) { return n % 251lu; }
static ft::prime_bs::prime_type mod397(ft::prime_bs::prime_type n) { return n % 397lu; }
static ft::prime_bs::prime_type mod797(ft::prime_bs::prime_type n) { return n % 797lu; }
static ft::prime_bs::prime_type mod1259(ft::prime_bs::prime_type n) { return n % 1259lu; }
static ft::prime_bs::prime_type mod2539(ft::prime_bs::prime_type n) { return n % 2539lu; }
static ft::prime_bs::prime_type mod4027(ft::prime_bs::prime_type n) { return n % 4027lu; }
static ft::prime_bs::prime_type mod6421(ft::prime_bs::prime_type n) { return n % 6421lu; }
static ft::prime_bs::prime_type mod8089(ft::prime_bs::prime_type n) { return n % 8089lu; }
static ft::prime_bs::prime_type mod10193(ft::prime_bs::prime_type n) { return n % 10193lu; }
static ft::prime_bs::prime_type mod12853(ft::prime_bs::prime_type n) { return n % 12853lu; }
static ft::prime_bs::prime_type mod16193(ft::prime_bs::prime_type n) { return n % 16193lu; }
static ft::prime_bs::prime_type mod20399(ft::prime_bs::prime_type n) { return n % 20399lu; }
static ft::prime_bs::prime_type mod25717(ft::prime_bs::prime_type n) { return n % 25717lu; }
static ft::prime_bs::prime_type mod32401(ft::prime_bs::prime_type n) { return n % 32401lu; }
static ft::prime_bs::prime_type mod40823(ft::prime_bs::prime_type n) { return n % 40823lu; }
static ft::prime_bs::prime_type mod51437(ft::prime_bs::prime_type n) { return n % 51437lu; }
static ft::prime_bs::prime_type mod64811(ft::prime_bs::prime_type n) { return n % 64811lu; }
static ft::prime_bs::prime_type mod81649(ft::prime_bs::prime_type n) { return n % 81649lu; }
static ft::prime_bs::prime_type mod102877(ft::prime_bs::prime_type n) { return n % 102877lu; }
static ft::prime_bs::prime_type mod129607(ft::prime_bs::prime_type n) { return n % 129607lu; }
static ft::prime_bs::prime_type mod163307(ft::prime_bs::prime_type n) { return n % 163307lu; }
static ft::prime_bs::prime_type mod205759(ft::prime_bs::prime_type n) { return n % 205759lu; }
static ft::prime_bs::prime_type mod259229(ft::prime_bs::prime_type n) { return n % 259229lu; }
static ft::prime_bs::prime_type mod326617(ft::prime_bs::prime_type n) { return n % 326617lu; }
static ft::prime_bs::prime_type mod411527(ft::prime_bs::prime_type n) { return n % 411527lu; }
static ft::prime_bs::prime_type mod518509(ft::prime_bs::prime_type n) { return n % 518509lu; }
static ft::prime_bs::prime_type mod653267(ft::prime_bs::prime_type n) { return n % 653267lu; }
static ft::prime_bs::prime_type mod823117(ft::prime_bs::prime_type n) { return n % 823117lu; }
static ft::prime_bs::prime_type mod1037059(ft::prime_bs::prime_type n) { return n % 1037059lu; }
static ft::prime_bs::prime_type mod1306601(ft::prime_bs::prime_type n) { return n % 1306601lu; }
static ft::prime_bs::prime_type mod1646237(ft::prime_bs::prime_type n) { return n % 1646237lu; }
static ft::prime_bs::prime_type mod2074129(ft::prime_bs::prime_type n) { return n % 2074129lu; }
static ft::prime_bs::prime_type mod2613229(ft::prime_bs::prime_type n) { return n % 2613229lu; }
static ft::prime_bs::prime_type mod3292489(ft::prime_bs::prime_type n) { return n % 3292489lu; }
static ft::prime_bs::prime_type mod4148279(ft::prime_bs::prime_type n) { return n % 4148279lu; }
static ft::prime_bs::prime_type mod5226491(ft::prime_bs::prime_type n) { return n % 5226491lu; }
static ft::prime_bs::prime_type mod6584983(ft::prime_bs::prime_type n) { return n % 6584983lu; }
static ft::prime_bs::prime_type mod8296553(ft::prime_bs::prime_type n) { return n % 8296553lu; }
static ft::prime_bs::prime_type mod10453007(ft::prime_bs::prime_type n) { return n % 10453007lu; }
static ft::prime_bs::prime_type mod13169977(ft::prime_bs::prime_type n) { return n % 13169977lu; }
static ft::prime_bs::prime_type mod16593127(ft::prime_bs::prime_type n) { return n % 16593127lu; }
static ft::prime_bs::prime_type mod20906033(ft::prime_bs::prime_type n) { return n % 20906033lu; }
static ft::prime_bs::prime_type mod26339969(ft::prime_bs::prime_type n) { return n % 26339969lu; }
static ft::prime_bs::prime_type mod33186281(ft::prime_bs::prime_type n) { return n % 33186281lu; }
static ft::prime_bs::prime_type mod41812097(ft::prime_bs::prime_type n) { return n % 41812097lu; }
static ft::prime_bs::prime_type mod52679969(ft::prime_bs::prime_type n) { return n % 52679969lu; }
static ft::prime_bs::prime_type mod66372617(ft::prime_bs::prime_type n) { return n % 66372617lu; }
static ft::prime_bs::prime_type mod83624237(ft::prime_bs::prime_type n) { return n % 83624237lu; }
static ft::prime_bs::prime_type mod105359939(ft::prime_bs::prime_type n) { return n % 105359939lu; }
static ft::prime_bs::prime_type mod132745199(ft::prime_bs::prime_type n) { return n % 132745199lu; }
static ft::prime_bs::prime_type mod167248483(ft::prime_bs::prime_type n) { return n % 167248483lu; }
static ft::prime_bs::prime_type mod210719881(ft::prime_bs::prime_type n) { return n % 210719881lu; }
static ft::prime_bs::prime_type mod265490441(ft::prime_bs::prime_type n) { return n % 265490441lu; }
static ft::prime_bs::prime_type mod334496971(ft::prime_bs::prime_type n) { return n % 334496971lu; }
static ft::prime_bs::prime_type mod421439783(ft::prime_bs::prime_type n) { return n % 421439783lu; }
static ft::prime_bs::prime_type mod530980861(ft::prime_bs::prime_type n) { return n % 530980861lu; }
static ft::prime_bs::prime_type mod668993977(ft::prime_bs::prime_type n) { return n % 668993977lu; }
static ft::prime_bs::prime_type mod842879579(ft::prime_bs::prime_type n) { return n % 842879579lu; }
static ft::prime_bs::prime_type mod1061961721(ft::prime_bs::prime_type n) { return n % 1061961721lu; }
static ft::prime_bs::prime_type mod1337987929(ft::prime_bs::prime_type n) { return n % 1337987929lu; }
static ft::prime_bs::prime_type mod1685759167(ft::prime_bs::prime_type n) { return n % 1685759167lu; }
static ft::prime_bs::prime_type mod2123923447(ft::prime_bs::prime_type n) { return n % 2123923447lu; }
static ft::prime_bs::prime_type mod2675975881(ft::prime_bs::prime_type n) { return n % 2675975881lu; }
static ft::prime_bs::prime_type mod3371518343(ft::prime_bs::prime_type n) { return n % 3371518343lu; }
static ft::prime_bs::prime_type mod4247846927(ft::prime_bs::prime_type n) { return n % 4247846927lu; }
static ft::prime_bs::prime_type mod5351951779(ft::prime_bs::prime_type n) { return n % 5351951779lu; }
static ft::prime_bs::prime_type mod6743036717(ft::prime_bs::prime_type n) { return n % 6743036717lu; }
static ft::prime_bs::prime_type mod8495693897(ft::prime_bs::prime_type n) { return n % 8495693897lu; }
static ft::prime_bs::prime_type mod10703903591(ft::prime_bs::prime_type n) { return n % 10703903591lu; }
static ft::prime_bs::prime_type mod13486073473(ft::prime_bs::prime_type n) { return n % 13486073473lu; }
static ft::prime_bs::prime_type mod16991387857(ft::prime_bs::prime_type n) { return n % 16991387857lu; }
static ft::prime_bs::prime_type mod21407807219(ft::prime_bs::prime_type n) { return n % 21407807219lu; }
static ft::prime_bs::prime_type mod26972146961(ft::prime_bs::prime_type n) { return n % 26972146961lu; }
static ft::prime_bs::prime_type mod33982775741(ft::prime_bs::prime_type n) { return n % 33982775741lu; }
static ft::prime_bs::prime_type mod42815614441(ft::prime_bs::prime_type n) { return n % 42815614441lu; }
static ft::prime_bs::prime_type mod53944293929(ft::prime_bs::prime_type n) { return n % 53944293929lu; }
static ft::prime_bs::prime_type mod67965551447(ft::prime_bs::prime_type n) { return n % 67965551447lu; }
static ft::prime_bs::prime_type mod85631228929(ft::prime_bs::prime_type n) { return n % 85631228929lu; }
static ft::prime_bs::prime_type mod107888587883(ft::prime_bs::prime_type n) { return n % 107888587883lu; }
static ft::prime_bs::prime_type mod135931102921(ft::prime_bs::prime_type n) { return n % 135931102921lu; }
static ft::prime_bs::prime_type mod171262457903(ft::prime_bs::prime_type n) { return n % 171262457903lu; }
static ft::prime_bs::prime_type mod215777175787(ft::prime_bs::prime_type n) { return n % 215777175787lu; }
static ft::prime_bs::prime_type mod271862205833(ft::prime_bs::prime_type n) { return n % 271862205833lu; }
static ft::prime_bs::prime_type mod342524915839(ft::prime_bs::prime_type n) { return n % 342524915839lu; }
static ft::prime_bs::prime_type mod431554351609(ft::prime_bs::prime_type n) { return n % 431554351609lu; }
static ft::prime_bs::prime_type mod543724411781(ft::prime_bs::prime_type n) { return n % 543724411781lu; }
static ft::prime_bs::prime_type mod685049831731(ft::prime_bs::prime_type n) { return n % 685049831731lu; }
static ft::prime_bs::prime_type mod863108703229(ft::prime_bs::prime_type n) { return n % 863108703229lu; }
static ft::prime_bs::prime_type mod1087448823553(ft::prime_bs::prime_type n) { return n % 1087448823553lu; }
static ft::prime_bs::prime_type mod1370099663459(ft::prime_bs::prime_type n) { return n % 1370099663459lu; }
static ft::prime_bs::prime_type mod1726217406467(ft::prime_bs::prime_type n) { return n % 1726217406467lu; }
static ft::prime_bs::prime_type mod2174897647073(ft::prime_bs::prime_type n) { return n % 2174897647073lu; }
static ft::prime_bs::prime_type mod2740199326961(ft::prime_bs::prime_type n) { return n % 2740199326961lu; }
static ft::prime_bs::prime_type mod3452434812973(ft::prime_bs::prime_type n) { return n % 3452434812973lu; }
static ft::prime_bs::prime_type mod4349795294267(ft::prime_bs::prime_type n) { return n % 4349795294267lu; }
static ft::prime_bs::prime_type mod5480398654009(ft::prime_bs::prime_type n) { return n % 5480398654009lu; }
static ft::prime_bs::prime_type mod6904869625999(ft::prime_bs::prime_type n) { return n % 6904869625999lu; }
static ft::prime_bs::prime_type mod8699590588571(ft::prime_bs::prime_type n) { return n % 8699590588571lu; }
static ft::prime_bs::prime_type mod10960797308051(ft::prime_bs::prime_type n) { return n % 10960797308051lu; }
static ft::prime_bs::prime_type mod13809739252051(ft::prime_bs::prime_type n) { return n % 13809739252051lu; }
static ft::prime_bs::prime_type mod17399181177241(ft::prime_bs::prime_type n) { return n % 17399181177241lu; }
static ft::prime_bs::prime_type mod21921594616111(ft::prime_bs::prime_type n) { return n % 21921594616111lu; }
static ft::prime_bs::prime_type mod27619478504183(ft::prime_bs::prime_type n) { return n % 27619478504183lu; }
static ft::prime_bs::prime_type mod34798362354533(ft::prime_bs::prime_type n) { return n % 34798362354533lu; }
static ft::prime_bs::prime_type mod43843189232363(ft::prime_bs::prime_type n) { return n % 43843189232363lu; }
static ft::prime_bs::prime_type mod55238957008387(ft::prime_bs::prime_type n) { return n % 55238957008387lu; }
static ft::prime_bs::prime_type mod69596724709081(ft::prime_bs::prime_type n) { return n % 69596724709081lu; }
static ft::prime_bs::prime_type mod87686378464759(ft::prime_bs::prime_type n) { return n % 87686378464759lu; }
static ft::prime_bs::prime_type mod110477914016779(ft::prime_bs::prime_type n) { return n % 110477914016779lu; }
static ft::prime_bs::prime_type mod139193449418173(ft::prime_bs::prime_type n) { return n % 139193449418173lu; }
static ft::prime_bs::prime_type mod175372756929481(ft::prime_bs::prime_type n) { return n % 175372756929481lu; }
static ft::prime_bs::prime_type mod220955828033581(ft::prime_bs::prime_type n) { return n % 220955828033581lu; }
static ft::prime_bs::prime_type mod278386898836457(ft::prime_bs::prime_type n) { return n % 278386898836457lu; }
static ft::prime_bs::prime_type mod350745513859007(ft::prime_bs::prime_type n) { return n % 350745513859007lu; }
static ft::prime_bs::prime_type mod441911656067171(ft::prime_bs::prime_type n) { return n % 441911656067171lu; }
static ft::prime_bs::prime_type mod556773797672909(ft::prime_bs::prime_type n) { return n % 556773797672909lu; }
static ft::prime_bs::prime_type mod701491027718027(ft::prime_bs::prime_type n) { return n % 701491027718027lu; }
static ft::prime_bs::prime_type mod883823312134381(ft::prime_bs::prime_type n) { return n % 883823312134381lu; }
static ft::prime_bs::prime_type mod1113547595345903(ft::prime_bs::prime_type n) { return n % 1113547595345903lu; }
static ft::prime_bs::prime_type mod1402982055436147(ft::prime_bs::prime_type n) { return n % 1402982055436147lu; }
static ft::prime_bs::prime_type mod1767646624268779(ft::prime_bs::prime_type n) { return n % 1767646624268779lu; }
static ft::prime_bs::prime_type mod2227095190691797(ft::prime_bs::prime_type n) { return n % 2227095190691797lu; }
static ft::prime_bs::prime_type mod2805964110872297(ft::prime_bs::prime_type n) { return n % 2805964110872297lu; }
static ft::prime_bs::prime_type mod3535293248537579(ft::prime_bs::prime_type n) { return n % 3535293248537579lu; }
static ft::prime_bs::prime_type mod4454190381383713(ft::prime_bs::prime_type n) { return n % 4454190381383713lu; }
static ft::prime_bs::prime_type mod5611928221744609(ft::prime_bs::prime_type n) { return n % 5611928221744609lu; }
static ft::prime_bs::prime_type mod7070586497075177(ft::prime_bs::prime_type n) { return n % 7070586497075177lu; }
static ft::prime_bs::prime_type mod8908380762767489(ft::prime_bs::prime_type n) { return n % 8908380762767489lu; }
static ft::prime_bs::prime_type mod11223856443489329(ft::prime_bs::prime_type n) { return n % 11223856443489329lu; }
static ft::prime_bs::prime_type mod14141172994150357(ft::prime_bs::prime_type n) { return n % 14141172994150357lu; }
static ft::prime_bs::prime_type mod17816761525534927(ft::prime_bs::prime_type n) { return n % 17816761525534927lu; }
static ft::prime_bs::prime_type mod22447712886978529(ft::prime_bs::prime_type n) { return n % 22447712886978529lu; }
static ft::prime_bs::prime_type mod28282345988300791(ft::prime_bs::prime_type n) { return n % 28282345988300791lu; }
static ft::prime_bs::prime_type mod35633523051069991(ft::prime_bs::prime_type n) { return n % 35633523051069991lu; }
static ft::prime_bs::prime_type mod44895425773957261(ft::prime_bs::prime_type n) { return n % 44895425773957261lu; }
static ft::prime_bs::prime_type mod56564691976601587(ft::prime_bs::prime_type n) { return n % 56564691976601587lu; }
static ft::prime_bs::prime_type mod71267046102139967(ft::prime_bs::prime_type n) { return n % 71267046102139967lu; }
static ft::prime_bs::prime_type mod89790851547914507(ft::prime_bs::prime_type n) { return n % 89790851547914507lu; }
static ft::prime_bs::prime_type mod113129383953203213(ft::prime_bs::prime_type n) { return n % 113129383953203213lu; }
static ft::prime_bs::prime_type mod142534092204280003(ft::prime_bs::prime_type n) { return n % 142534092204280003lu; }
static ft::prime_bs::prime_type mod179581703095829107(ft::prime_bs::prime_type n) { return n % 179581703095829107lu; }
static ft::prime_bs::prime_type mod226258767906406483(ft::prime_bs::prime_type n) { return n % 226258767906406483lu; }
static ft::prime_bs::prime_type mod285068184408560057(ft::prime_bs::prime_type n) { return n % 285068184408560057lu; }
static ft::prime_bs::prime_type mod359163406191658253(ft::prime_bs::prime_type n) { return n % 359163406191658253lu; }
static ft::prime_bs::prime_type mod452517535812813007(ft::prime_bs::prime_type n) { return n % 452517535812813007lu; }
static ft::prime_bs::prime_type mod570136368817120201(ft::prime_bs::prime_type n) { return n % 570136368817120201lu; }
static ft::prime_bs::prime_type mod718326812383316683(ft::prime_bs::prime_type n) { return n % 718326812383316683lu; }
static ft::prime_bs::prime_type mod905035071625626043(ft::prime_bs::prime_type n) { return n % 905035071625626043lu; }
static ft::prime_bs::prime_type mod1140272737634240411(ft::prime_bs::prime_type n) { return n % 1140272737634240411lu; }
static ft::prime_bs::prime_type mod1436653624766633509(ft::prime_bs::prime_type n) { return n % 1436653624766633509lu; }
static ft::prime_bs::prime_type mod1810070143251252131(ft::prime_bs::prime_type n) { return n % 1810070143251252131lu; }
static ft::prime_bs::prime_type mod2280545475268481167(ft::prime_bs::prime_type n) { return n % 2280545475268481167lu; }
static ft::prime_bs::prime_type mod2873307249533267101(ft::prime_bs::prime_type n) { return n % 2873307249533267101lu; }
static ft::prime_bs::prime_type mod3620140286502504283(ft::prime_bs::prime_type n) { return n % 3620140286502504283lu; }
static ft::prime_bs::prime_type mod4561090950536962147(ft::prime_bs::prime_type n) { return n % 4561090950536962147lu; }
static ft::prime_bs::prime_type mod5746614499066534157(ft::prime_bs::prime_type n) { return n % 5746614499066534157lu; }
static ft::prime_bs::prime_type mod7240280573005008577(ft::prime_bs::prime_type n) { return n % 7240280573005008577lu; }
static ft::prime_bs::prime_type mod9122181901073924329(ft::prime_bs::prime_type n) { return n % 9122181901073924329lu; }
static ft::prime_bs::prime_type mod11493228998133068689(ft::prime_bs::prime_type n) { return n % 11493228998133068689lu; }
static ft::prime_bs::prime_type mod14480561146010017169(ft::prime_bs::prime_type n) { return n % 14480561146010017169lu; }
static ft::prime_bs::prime_type mod18446744073709551557(ft::prime_bs::prime_type n) { return n % 18446744073709551557lu; }

/*
** List holding all the function pointers
*/
ft::prime_bs::mod_type ft::prime_bs::spec_mod[] = {
	&mod37, &mod59, &mod127,
	&mod251, &mod397, &mod797,
	&mod1259, &mod2539, &mod4027,
	&mod6421, &mod8089, &mod10193,
	&mod12853, &mod16193, &mod20399,
	&mod25717, &mod32401, &mod40823,
	&mod51437, &mod64811, &mod81649,
	&mod102877, &mod129607, &mod163307,
	&mod205759, &mod259229, &mod326617,
	&mod411527, &mod518509, &mod653267,
	&mod823117, &mod1037059, &mod1306601,
	&mod1646237, &mod2074129, &mod2613229,
	&mod3292489, &mod4148279, &mod5226491,
	&mod6584983, &mod8296553, &mod10453007,
	&mod13169977, &mod16593127, &mod20906033,
	&mod26339969, &mod33186281, &mod41812097,
	&mod52679969, &mod66372617, &mod83624237,
	&mod105359939, &mod132745199, &mod167248483,
	&mod210719881,&mod265490441, &mod334496971,
	&mod421439783, &mod530980861, &mod668993977,
	&mod842879579, &mod1061961721, &mod1337987929,
	&mod1685759167, &mod2123923447, &mod2675975881,
	&mod3371518343, &mod4247846927, &mod5351951779,
	&mod6743036717, &mod8495693897, &mod10703903591,
	&mod13486073473, &mod16991387857, &mod21407807219,
	&mod26972146961, &mod33982775741, &mod42815614441,
	&mod53944293929, &mod67965551447, &mod85631228929, 
	&mod107888587883, &mod135931102921, &mod171262457903,
	&mod215777175787, &mod271862205833, &mod342524915839,
	&mod431554351609, &mod543724411781, &mod685049831731,
	&mod863108703229, &mod1087448823553, &mod1370099663459,
	&mod1726217406467, &mod2174897647073, &mod2740199326961,
	&mod3452434812973, &mod4349795294267, &mod5480398654009,
	&mod6904869625999, &mod8699590588571, &mod10960797308051,
	&mod13809739252051, &mod17399181177241, &mod21921594616111,
	&mod27619478504183, &mod34798362354533, &mod43843189232363,
	&mod55238957008387, &mod69596724709081, &mod87686378464759,
	&mod110477914016779, &mod139193449418173, &mod175372756929481,
	&mod220955828033581, &mod278386898836457, &mod350745513859007,
	&mod441911656067171, &mod556773797672909, &mod701491027718027,
	&mod883823312134381, &mod1113547595345903, &mod1402982055436147,
	&mod1767646624268779, &mod2227095190691797, &mod2805964110872297,
	&mod3535293248537579, &mod4454190381383713, &mod5611928221744609,
	&mod7070586497075177, &mod8908380762767489, &mod11223856443489329,
	&mod14141172994150357, &mod17816761525534927, &mod22447712886978529,
	&mod28282345988300791, &mod35633523051069991, &mod44895425773957261,
	&mod56564691976601587, &mod71267046102139967, &mod89790851547914507,
	&mod113129383953203213, &mod142534092204280003, &mod179581703095829107,
	&mod226258767906406483, &mod285068184408560057, &mod359163406191658253,
	&mod452517535812813007, &mod570136368817120201, &mod718326812383316683,
	&mod905035071625626043, &mod1140272737634240411, &mod1436653624766633509,
	&mod1810070143251252131, &mod2280545475268481167, &mod2873307249533267101,
	&mod3620140286502504283, &mod4561090950536962147, &mod5746614499066534157,
	&mod7240280573005008577, &mod9122181901073924329, &mod11493228998133068689,
	&mod14480561146010017169, &mod18446744073709551557
};
