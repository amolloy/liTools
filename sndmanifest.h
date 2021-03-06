#include "pakDataTypes.h"

extern void initSoundManifest();

typedef struct
{
	u32 id;
	const char* name;
} soundMap;

const auto SND_NUM_MAPPINGS = 275;

const soundMap g_soundMap[SND_NUM_MAPPINGS] = {{1493394940u, "data/animations/Intro/matchStrike.flac"},
{2504560674u, "data/animations/Scene_MsNancyRocket/RocketLaunch.flac"},
{2094482604u, "data/characters/msNancy/voice/type.flac"},
{1176241121u, "data/characters/SugarPlumps/voice/badConnection.flac"},
{3097582099u, "data/characters/SugarPlumps/voice/nomnomnom.flac"},
{3656305786u, "data/characters/SugarPlumps/voice/shadowHangup.flac"},
{2274798221u, "data/characters/SugarPlumps/voice/shadowType.flac"},
{2381232218u, "data/characters/SugarPlumps/voice/shhh.flac"},
{1484057000u, "data/characters/SugarPlumps/voice/smooch.flac"},
{613241189u, "data/characters/SugarPlumps/voice/smoochBig.flac"},
{484346969u, "data/characters/SugarPlumps/voice/type.flac"},
{1749472574u, "data/characters/weatherman/voice/type.flac"},
{4145851370u, "data/cutscenes/Jingle/audiosync.flac"},
{2474343835u, "data/cutscenes/MsNancyHug/hugSync.flac"},
{505060496u, "data/cutscenes/OpenTheGatesDramatic/OpenTheGatesJustLever.flac"},
{501810722u, "data/items/_common/beep.flac"},
{3148128828u, "data/items/AbsoluteSpawner/CreationismRain.flac"},
{1945248028u, "data/items/AlarmClock/windupRingBreak.flac"},
{108989433u, "data/items/Balloons/pop.flac"},
{3998510924u, "data/items/Bank/Buzzer.flac"},
{3947315401u, "data/items/Bank/CasinoPayout.flac"},
{3058969825u, "data/items/Bank/Spin.flac"},
{1838957405u, "data/items/BearTrapSitting/snap.flac"},
{4062428893u, "data/items/Bubble/pop.flac"},
{2736125712u, "data/items/Camera/snapshot.flac"},
{4292572444u, "data/items/CardboardSword/endOfAdventure.flac"},
{1833890506u, "data/items/CasualGame/underwhelmingApplause.flac"},
{2390963778u, "data/items/CelebrationBus/screaming.flac"},
{1121972044u, "data/items/Cello/collide.flac"},
{98544330u, "data/items/Cello/swan.flac"},
{793214772u, "data/items/CellPhone/beep.flac"},
{1335764677u, "data/items/CellPhone/TelephoneErrorMessage.flac"},
{152190458u, "data/items/Cigarettes/exhale.flac"},
{558195556u, "data/items/Cocoon/flutter.flac"},
{2943622278u, "data/items/CreditCard/burn.flac"},
{1978747166u, "data/items/DollZombie/grab.flac"},
{3700910994u, "data/items/DollZombie/zombieBurn.flac"},
{2249095001u, "data/items/DrillChainThrower/cut.flac"},
{1017931524u, "data/items/DrillChainThrower/loop.flac"},
{2039897619u, "data/items/DrillChainThrower/start.flac"},
{3515690409u, "data/items/Exterminator/chargingUp.flac"},
{3182349421u, "data/items/Exterminator/grab.flac"},
{2023008337u, "data/items/Extinction/crack2.flac"},
{2122567835u, "data/items/Extinction/Squeal.flac"},
{3560091973u, "data/items/Factory/Factory.flac"},
{3911388779u, "data/items/Factory/makePerson.flac"},
{2319887458u, "data/items/FeelieBear/burn.flac"},
{224435296u, "data/items/FeelieBear/grab.flac"},
{2123252246u, "data/items/GalaxyCollection/tinyScreams.flac"},
{3580293212u, "data/items/GameBushDuck/duckSpawn.flac"},
{2487011326u, "data/items/GameBushDuck/gunShot.flac"},
{3043343329u, "data/items/GentlemanExplorer/burn.flac"},
{843287523u, "data/items/GentlemanExplorer/grab.flac"},
{3741165192u, "data/items/GooBallPack/death.flac"},
{435616795u, "data/items/GooBallPack/glee.flac"},
{3380346793u, "data/items/GooBallPack/mumble.flac"},
{948030701u, "data/items/GravityBoy/grab.flac"},
{3908748446u, "data/items/GravityBoy/gravityBoy.flac"},
{4173604661u, "data/items/HandheldFire/8BitInferno.flac"},
{4018499497u, "data/items/HandheldFire/HandheldEnd.flac"},
{1555031932u, "data/items/HandheldFire/HandheldLoseLife.flac"},
{3818859677u, "data/items/HowlingCoyote/howl.flac"},
{2592200801u, "data/items/IceCube/IceBreak.flac"},
{3550178071u, "data/items/InternetCloud/internetBurn.flac"},
{4071548199u, "data/items/KittyKittyPooPoo/grab.flac"},
{3853693218u, "data/items/KittyKittyPooPoo/meow.flac"},
{3650889421u, "data/items/KittyKittyPooPoo/poo.flac"},
{1551305163u, "data/items/KnockoffGamingDevice/bootUp.flac"},
{124317926u, "data/items/KnockoffGamingDevice/game.flac"},
{1308402250u, "data/items/KnockoffGamingDevice/game02.flac"},
{335154250u, "data/items/LadyBug/attractSound.flac"},
{2138109441u, "data/items/Laser/bleepA.flac"},
{2138110465u, "data/items/Laser/bleepB.flac"},
{789181646u, "data/items/Leperchaun/grabgrab.flac"},
{441932657u, "data/items/Leperchaun/lepGiggle.flac"},
{550037148u, "data/items/LittleInfernoBeta/BetaMusic.flac"},
{3969786890u, "data/items/LocustEggs/swarm.flac"},
{1683471734u, "data/items/LowSelfEsteemGirl/burn.flac"},
{3815869812u, "data/items/LowSelfEsteemGirl/grab.flac"},
{1797849041u, "data/items/Magnet/gearRotate.flac"},
{136269885u, "data/items/ManlyOdorSpray/spray.flac"},
{3619769502u, "data/items/Marshmallow/death.flac"},
{3673248670u, "data/items/Marshmallow/hello.flac"},
{1496234707u, "data/items/MechanicalHeart/heartLoop.flac"},
{2733105957u, "data/items/MiniatureSun/SunLoop.flac"},
{251662440u, "data/items/MomAndDadBots/decharge.flac"},
{3812447921u, "data/items/MusicTones/a.flac"},
{3812448945u, "data/items/MusicTones/b.flac"},
{3812449969u, "data/items/MusicTones/c.flac"},
{3812442801u, "data/items/MusicTones/d.flac"},
{3812443825u, "data/items/MusicTones/e.flac"},
{3812444849u, "data/items/MusicTones/f.flac"},
{3812445873u, "data/items/MusicTones/g.flac"},
{2501511126u, "data/items/MustacheRider/loop.flac"},
{2728802119u, "data/items/MustacheRider/start.flac"},
{280903920u, "data/items/Ninja/grab.flac"},
{577029361u, "data/items/Ninja/ninjaVanish.flac"},
{2899119420u, "data/items/OilBarge/flameBurst.flac"},
{1926637801u, "data/items/OilBarge/FogHorn.flac"},
{1970964518u, "data/items/OldLady/burn.flac"},
{4066162724u, "data/items/OldLady/grab.flac"},
{1558561130u, "data/items/Phoenix/Phoenix.flac"},
{3018384752u, "data/items/Pirate/burn.flac"},
{885970290u, "data/items/Pirate/grab.flac"},
{2832815396u, "data/items/Politician/burn.flac"},
{805266726u, "data/items/Politician/grab.flac"},
{2808118759u, "data/items/Popcorn/pop.flac"},
{90094683u, "data/items/QuadBunnyRazor/grab.flac"},
{3824836892u, "data/items/QuadBunnyRazor/MotorChompChomp.flac"},
{2355320344u, "data/items/Raccoon/grab.flac"},
{2749560898u, "data/items/Raccoon/squeal.flac"},
{3433766211u, "data/items/Radio/radio_tuningTheme.flac"},
{728390141u, "data/items/RailroadXing/trainXing.flac"},
{2627570396u, "data/items/Razer/bzzzz.flac"},
{4152371304u, "data/items/RocketShipOfLearning/blastOff.flac"},
{3770243963u, "data/items/Scarecrow/distantCrows.flac"},
{1846730412u, "data/items/SCKatie/BurnLikeMyHeart.flac"},
{1417684496u, "data/items/SCKatie/grab.flac"},
{3402177880u, "data/items/SmokeDetector/alarm.flac"},
{2316684945u, "data/items/SmokeDetector/sprinkler.flac"},
{2403983067u, "data/items/SonicBoomBox/loudmusic.flac"},
{2147661335u, "data/items/SouthPole/coldWind.flac"},
{1868941115u, "data/items/SpaceHeater/fanLoop.flac"},
{1746876661u, "data/items/SpiderEgg/babySpew.flac"},
{280043358u, "data/items/SquirrelWhistle/swhistle.flac"},
{1713213678u, "data/items/SuperJuicer4000/cut.flac"},
{3110428785u, "data/items/SuperJuicer4000/SuperJuicer.flac"},
{2878683186u, "data/items/SuperJuicer4000/SuperJuicerStart.flac"},
{1750385040u, "data/items/Tetrominos/lineBreak.flac"},
{2292507108u, "data/items/Tetrominos/quadBreak.flac"},
{2909183435u, "data/items/TheTerribleSecret/shhhhh.flac"},
{3560811979u, "data/items/TikiTorch/burn.flac"},
{1188280082u, "data/items/Toaster/toasterPop.flac"},
{2290986635u, "data/items/Transhumanist/TranshumanistConnects.flac"},
{3877299198u, "data/items/TRex/grr.flac"},
{3382303318u, "data/items/TRex/grrab.flac"},
{1678329572u, "data/items/TV/staticLoop.flac"},
{3389406751u, "data/items/UncleSamBamBam/FireworkWhistle.flac"},
{1261045615u, "data/items/UnhappyElf/grab.flac"},
{1445607274u, "data/items/UnhappyElf/Moan.flac"},
{1176735615u, "data/items/UnstableOrdinance/jetFlying.flac"},
{3950293269u, "data/items/Valkyrie/grab.flac"},
{534316852u, "data/items/Valkyrie/opera.flac"},
{995651059u, "data/items/WindupBot/toyMotor.flac"},
{3371678856u, "data/items/WoodenIdol1/choir_C.flac"},
{3371672708u, "data/items/WoodenIdol2/choir_E.flac"},
{3371674752u, "data/items/WoodenIdol3/choir_G.flac"},
{1213037071u, "data/music/Credits.flac"},
{1701623807u, "data/music/Gate Operator, Open the Gates!.flac"},
{735702279u, "data/music/LittleInfernoTitles.flac"},
{3814536959u, "data/music/MissNancyWelcomesYou.flac"},
{2557329964u, "data/music/ProductivityTango_loop.flac"},
{3791452086u, "data/music/ReportingFromTheWeatherBalloon_loop.flac"},
{1730772514u, "data/music/SugarPlumps_1.5_SomethingToTellYou.flac"},
{313357266u, "data/music/SugarPlumps_1_BestFriends.flac"},
{3306171218u, "data/music/SugarPlumps_2_JustLikeYou.flac"},
{1151899540u, "data/music/SugarPlumps_3_UpUpTheChimney.flac"},
{3123863486u, "data/music/SugarPlumps_4_ThisIsIt.flac"},
{2362683736u, "data/music/SugarPlumps_5_OooItsSoBright!.flac"},
{353039966u, "data/music/TEMP_Catalog.flac"},
{3376288268u, "data/music/TheCity.flac"},
{3200324344u, "data/music/TheCity_choirTrack.flac"},
{502778898u, "data/music/TheCityLimits.flac"},
{276510347u, "data/music/WeathermanSpeaks.flac"},
{1082572453u, "data/scenes/TomorrowCorpLobby/elevatorDoor_close.flac"},
{3621141060u, "data/scenes/TomorrowCorpLobby/elevatorDoor_open.flac"},
{2794942216u, "data/SFX/ambience/city.flac"},
{640291499u, "data/SFX/ambience/citySubway.flac"},
{4047458256u, "data/SFX/ambience/room1.flac"},
{2057094751u, "data/SFX/ambience/skyline.flac"},
{2061339806u, "data/SFX/ambience/warning.flac"},
{2094868009u, "data/SFX/catalog/buy.flac"},
{2188973818u, "data/SFX/catalog/buyCheer.flac"},
{2183167805u, "data/SFX/catalog/cardFlip.flac"},
{783572608u, "data/SFX/catalog/cardHover.flac"},
{3971329256u, "data/SFX/catalog/catalogClose.flac"},
{1284398176u, "data/SFX/catalog/catalogOpen.flac"},
{3029102664u, "data/SFX/catalog/paperflip.flac"},
{818733088u, "data/SFX/cheer.flac"},
{208104489u, "data/SFX/coinPickup.flac"},
{2878670927u, "data/SFX/collision/8bit.flac"},
{1728576146u, "data/SFX/collision/bleep.flac"},
{2779004131u, "data/SFX/collision/cardboard.flac"},
{4034584608u, "data/SFX/collision/cardboardHollow.flac"},
{3943759571u, "data/SFX/collision/coin1.flac"},
{2374229137u, "data/SFX/collision/generic.flac"},
{1663825874u, "data/SFX/collision/glass.flac"},
{1139290818u, "data/SFX/collision/metalLarge.flac"},
{1536753642u, "data/SFX/collision/metalMedium.flac"},
{1358827780u, "data/SFX/collision/metalSmall.flac"},
{1733572338u, "data/SFX/collision/paperRattle.flac"},
{2109197077u, "data/SFX/collision/paperSolid.flac"},
{2793501802u, "data/SFX/collision/rock.flac"},
{10224808u, "data/SFX/collision/woodMedium.flac"},
{3561494770u, "data/SFX/collision/woodSmall.flac"},
{1228288122u, "data/SFX/couponPickup.flac"},
{3010300136u, "data/SFX/curtainsFall.flac"},
{3014366414u, "data/SFX/deleteScreams.flac"},
{450042976u, "data/SFX/dialog_flip.flac"},
{165290276u, "data/SFX/dialog_responseSelect.flac"},
{644102116u, "data/SFX/eggCrack.flac"},
{3780508514u, "data/SFX/explodeBeetle.flac"},
{1403506507u, "data/SFX/explodeLarge.flac"},
{2087074658u, "data/SFX/explodeMedium.flac"},
{3748692790u, "data/SFX/explodePop.flac"},
{1085402253u, "data/SFX/explodeSmall.flac"},
{815725163u, "data/SFX/fireLoop.flac"},
{3335759667u, "data/SFX/fireplaceAmbience01.flac"},
{3335761715u, "data/SFX/fireplaceAmbience03.flac"},
{3773806706u, "data/SFX/footsteps/step_carpet.flac"},
{11557390u, "data/SFX/footsteps/step_snow.flac"},
{3351325016u, "data/SFX/freeze.flac"},
{1571089308u, "data/SFX/glassShatterLarge.flac"},
{2113163493u, "data/SFX/glassShatterMedium.flac"},
{1320339546u, "data/SFX/glassShatterSmall.flac"},
{874039219u, "data/SFX/grab/bug.flac"},
{3365963482u, "data/SFX/grab/cloth.flac"},
{3263859413u, "data/SFX/grab/creak.flac"},
{3333352410u, "data/SFX/grab/glass.flac"},
{825026483u, "data/SFX/grab/goo.flac"},
{2275344030u, "data/SFX/grab/metalDish.flac"},
{1468197404u, "data/SFX/grab/paper.flac"},
{3083501138u, "data/SFX/grab/rock.flac"},
{1744472290u, "data/SFX/grab/rubber.flac"},
{1436851934u, "data/SFX/grab/servo.flac"},
{935330386u, "data/SFX/grab/soft.flac"},
{3917969515u, "data/SFX/grab/underwater.flac"},
{830809573u, "data/SFX/grab/woodRattle.flac"},
{1578125618u, "data/SFX/grab/woodSmall.flac"},
{693119571u, "data/SFX/helloFireplace.flac"},
{1159793716u, "data/SFX/houseBurns/1_inside.flac"},
{1011278883u, "data/SFX/houseBurns/2_outside.flac"},
{3107247336u, "data/SFX/houseBurns/coinRoll1.flac"},
{3107248360u, "data/SFX/houseBurns/coinRoll2.flac"},
{3107249384u, "data/SFX/houseBurns/coinRoll3.flac"},
{2672212849u, "data/SFX/houseBurns/errorCombo1.flac"},
{2672211825u, "data/SFX/houseBurns/errorCombo2.flac"},
{2672210801u, "data/SFX/houseBurns/errorCombo3.flac"},
{1457130137u, "data/SFX/houseBurns/rip.flac"},
{4056543076u, "data/SFX/houseBurns/ripHorn.flac"},
{414474100u, "data/SFX/houseBurns/rumbleLoop.flac"},
{965231300u, "data/SFX/houseBurns/segmentBegin.flac"},
{4215332017u, "data/SFX/houseBurns/stampRoll1.flac"},
{4215328945u, "data/SFX/houseBurns/stampRoll2.flac"},
{4215329969u, "data/SFX/houseBurns/stampRoll3.flac"},
{2380623622u, "data/SFX/ignite/bigClean.flac"},
{1662805921u, "data/SFX/ignite/genericLarge.flac"},
{565333626u, "data/SFX/ignite/genericMedium.flac"},
{1879721063u, "data/SFX/ignite/genericSmall.flac"},
{911887515u, "data/SFX/ignite/hiss.flac"},
{744477296u, "data/SFX/mail/flip.flac"},
{2957486708u, "data/SFX/mail/open.flac"},
{3597850423u, "data/SFX/mail/sugarplumps/breakGlass1.flac"},
{3597851447u, "data/SFX/mail/sugarplumps/breakGlass2.flac"},
{60568246u, "data/SFX/mail/sugarplumps/breakJar.flac"},
{1271921239u, "data/SFX/mail/sugarplumps/exterminatorBeep.flac"},
{3260739681u, "data/SFX/mail/sugarplumps/exterminatorBlast.flac"},
{2382335521u, "data/SFX/mail/sugarplumps/exterminatorCharge.flac"},
{4243878153u, "data/SFX/mail/sugarplumps/houseBurns.flac"},
{4104498596u, "data/SFX/mail/sugarplumps/scratch_long.flac"},
{1869827001u, "data/SFX/mail/sugarplumps/scratch_three.flac"},
{2289532563u, "data/SFX/mail/sugarplumps/wallKnocking.flac"},
{3018108749u, "data/SFX/plague/plague.flac"},
{3586390330u, "data/SFX/plague/rot.flac"},
{3408402080u, "data/SFX/popup_enter.flac"},
{3606009770u, "data/SFX/popup_exit.flac"},
{3288753766u, "data/SFX/sootbugs/squirm.flac"},
{887259180u, "data/SFX/spark.flac"},
{3419520400u, "data/SFX/squish.flac"},
{1391016466u, "data/SFX/topPop.flac"},
{3242755097u, "data/SFX/tray/boxOpen.flac"},
{3626421439u, "data/SFX/tray/expressShipClose.flac"},
{3806821024u, "data/SFX/tray/expressShipOpen.flac"},
{718368276u, "data/SFX/tray/grow.flac"},
{3453041629u, "data/SFX/whoosh.flac"}};
