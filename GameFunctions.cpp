#include "GameFunctions.h"

GameFunctions::GameFunctions()
{
    is_quit = false;
    running = true;
    menu = INTRO;
}

GameFunctions::~GameFunctions()
{

}

bool GameFunctions::InitData()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return false;
    g_window = SDL_CreateWindow("Cat and Shark", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        return false;
    }
    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_screen == NULL) return false;
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) && imgFlags))
            return false;
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)== -1)
        {
            return false;
        }
        background_ = Mix_LoadMUS("sound//background.mp3");
        intro_ = Mix_LoadMUS("sound//intro.mp3");
        injured_ = Mix_LoadWAV("sound//injured.wav");
        cat_bullet = Mix_LoadWAV("sound//meow.mp3");
        success_eat = Mix_LoadWAV("sound//get_bonus.mp3");
        s_game_over = Mix_LoadWAV("sound//game_over.mp3");
        if (background_ == NULL || intro_ == NULL || injured_ == NULL||cat_bullet == NULL
            ||success_eat == NULL|| s_game_over == NULL)
        {
            cout << "Fail to load sound";
            return false;
        }
        if (TTF_Init() == -1) return false;
        g_font = TTF_OpenFont("font//PressStart2P.ttf", 20);
        g_font_intro = TTF_OpenFont("font//PressStart2P.ttf", 30);
        g_font_end = TTF_OpenFont("font//PressStart2P.ttf", 77);
        g_font_choose = TTF_OpenFont("font//Quantico.ttf", 50);
        if (g_font == NULL || g_font_intro == NULL || g_font_end == NULL ||g_font_choose == NULL) {
            cout << "Fail to load font";
            return false;
        }
    }
    cat_obj.LoadImg("img//catsheet.png", g_screen);
    cat_obj.LoadInjured("img//cat_hurt1.png", g_screen);
    heart.LoadImg("img//heart.png", g_screen);
    heart.SetWidth(40, 25);
    heart.SetRect(SCREEN_WIDTH/2 - heart.GetRect().w, 0);
    textX.LoadText(g_font, "x", color_text, g_screen);
    textX.SetRect(SCREEN_WIDTH/2 - heart.GetRect().w + 50, heart.GetRect().h/2-textX.GetRect().h/2);
    number_life.SetValue(LIFES);
    number_life.SetRect(SCREEN_WIDTH/2 - heart.GetRect().w+50+heart.GetRect().w, heart.GetRect().h/2-textX.GetRect().h/2);
    show_bullet.LoadText(g_font, "USE LEFT MOUSE BUTTON TO SHOOT",color_text, g_screen);
    show_bullet.SetRect(SCREEN_WIDTH/2 - show_bullet.GetRect().w/2, 25);
    return true;
}

bool GameFunctions::CheckMouse(int &x, int &y, SDL_Rect rect_mouse)
{
    if (x >=rect_mouse.x && x <= rect_mouse.x+rect_mouse.w
        && y >= rect_mouse.y && y <= rect_mouse.y+rect_mouse.h)
        return true;
    return false;
}

bool GameFunctions::ShowIntro()
{
    cout << "NEW GAME!\n";
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    Mix_VolumeMusic(MIX_MAX_VOLUME);
    Mix_VolumeChunk(cat_bullet, MIX_MAX_VOLUME);
    Mix_VolumeChunk(s_game_over, MIX_MAX_VOLUME);
    Mix_VolumeChunk(success_eat, MIX_MAX_VOLUME);
    Mix_VolumeChunk(injured_, MIX_MAX_VOLUME);
    running = true;
    SDL_Surface* surface = IMG_Load("img//cursor.png");
    SDL_Cursor* cursor = SDL_CreateColorCursor(surface, 0,0);
    SDL_SetCursor(cursor);

    LTexture bg_intro(g_screen, rect_screen);
    bg_intro.loadFromFile("img//intro.png");

    LTexture bg_htp(g_screen, rect_screen);
    bg_htp.loadFromFile("img//htp.png");

    SDL_Rect rect_sound = {5, 5, 29, 24};
    LTexture sound_(g_screen, rect_sound);
    sound_.loadFromFile("img//sound.png");
    bool select_sound = 0;

    Cat cat_intro;
    cat_intro.LoadImg("img//catsheet.png", g_screen);
    cat_intro.SetWidth(160, 120);
    cat_intro.SetRect(400, 100);

    Shark shark_intro;
    shark_intro.LoadImg("img//sharksheet.png", g_screen);
    shark_intro.SetRect(600, 330);
    shark_intro.SetWidth(192, 111);
    Mix_PlayMusic(intro_ , 10);

    GameText intro_t[3];
    string text[3] = {"Play", "How To Play", "Quit" };
    SDL_Rect rect_intro[3];
    bool selected[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        intro_t[i].LoadText(g_font_intro, text[i], color_intro, g_screen);
        intro_t[i].SetRect(70, 220 + 70*i);
        rect_intro[i] = intro_t[i].GetRect();
    }

    GameText back_;
    back_.LoadText(g_font, "Back", color_intro, g_screen);
    back_.SetRect(SCREEN_WIDTH/2 - 20, 470);

    LTexture bg(g_screen, rect_screen);
    bg.loadFromFile("img//bg.jpg");
    GameText chooseBgText;
    chooseBgText.LoadText(g_font_choose, "CHOOSE BACKGROUND", color_intro, g_screen);
    chooseBgText.SetRect(SCREEN_WIDTH/2 - chooseBgText.GetRect().w/2, 100);
    GameText choose_bg[5];
    string c_text[5] = {"Underwater", "Sky", "Universe", "City", "Back"};
    SDL_Rect rect_choose[5];
    bool c_selected[5] = {0, 0, 0, 0 ,0};
    for (int i = 0; i < 5; i++) {
        choose_bg[i].LoadText(g_font, c_text[i], color_intro, g_screen );
        choose_bg[i].SetRect(100, 200+i*50);
        rect_choose[i] = choose_bg[i].GetRect();
    }
	int x, y;
	while (running)
	{
	    SDL_RenderClear(g_screen);
	    if (menu == INTRO) {
            bg_intro.render();
            cat_intro.ShowAnimation(g_screen);
            shark_intro.ShowSharkAnimation(g_screen);
            sound_.render();
            for (int i = 0; i < 3; i++)
            {
                intro_t[i].Present(g_screen);
            }
	    }
	    else if (menu == HTP) {
            bg_htp.render();
            back_.Present(g_screen);
            sound_.render();
        }
	    else if (menu == CHOOSE)
        {
            bg.render();
            chooseBgText.Present(g_screen);
            for (int i = 0; i < 5; i++) {
                choose_bg[i].Present(g_screen);
            }
            sound_.render();
        }
		while (SDL_PollEvent(&g_event))
		{
			switch (g_event.type)
			{
                case SDL_QUIT:
                {
                    running = false;
                    return 0;
                }
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    if (menu == INTRO) {
                        for (int i = 0; i < 3; i++)
                        {
                            if (CheckMouse(x, y, rect_intro[i]))
                            {
                                if (!selected[i])
                                {
                                    selected[i] = 1;
                                    if (i == 2) {
                                        intro_t[i].LoadText(g_font_intro, text[i], color_exit, g_screen);
                                    } else {
                                        intro_t[i].LoadText(g_font_intro, text[i], color_select, g_screen);
                                    }
                                }
                            }
                            else
                            {
                                if (selected[i])
                                {
                                    selected[i] = 0;
                                    intro_t[i].LoadText(g_font_intro, text[i], color_intro, g_screen);
                                }
                            }
                        }
                    }
                    else if (menu == HTP) {
                        if (CheckMouse(x, y, back_.GetRect()))
                        {
                            back_.LoadText(g_font, "Back", color_select, g_screen);
                        }
                        else {
                            back_.LoadText(g_font, "Back", color_intro, g_screen);
                        }
                    }
                    else if (menu == CHOOSE)
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            if (CheckMouse(x, y, rect_choose[i]))
                            {
                                if (!c_selected[i]) {
                                    c_selected[i] = 1;
                                    choose_bg[i].LoadText(g_font, c_text[i], color_select, g_screen);
                                }

                            }
                            else
                            {
                                if (c_selected[i]) {
                                    c_selected[i] = 0;
                                    choose_bg[i].LoadText(g_font, c_text[i], color_intro, g_screen);
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN: {
                    x = g_event.button.x;
                    y = g_event.button.y;
                    if (CheckMouse(x, y, rect_sound)) {
                        if (!select_sound) {
                            select_sound = 1;
                            Mix_VolumeMusic(0);
                            Mix_VolumeChunk(cat_bullet, 0);
                            Mix_VolumeChunk(s_game_over, 0);
                            Mix_VolumeChunk(success_eat, 0);
                            Mix_VolumeChunk(injured_, 0);
                            sound_.loadFromFile("img//mute.png");
                        }
                        else{
                            select_sound = 0;
                            Mix_VolumeMusic(MIX_MAX_VOLUME);
                            Mix_VolumeChunk(cat_bullet, MIX_MAX_VOLUME);
                            Mix_VolumeChunk(s_game_over, MIX_MAX_VOLUME);
                            Mix_VolumeChunk(success_eat, MIX_MAX_VOLUME);
                            Mix_VolumeChunk(injured_, MIX_MAX_VOLUME);
                            sound_.loadFromFile("img//sound.png");
                        }
                    }
                    if (menu == INTRO) {
                        for (int i = 0; i < 3; i++)
                        {
                            if (CheckMouse(x, y, rect_intro[i])) {
                                if (i == 0) {
                                    menu = CHOOSE;
                                }
                                else if (i == 1) {
                                    menu = HTP;
                                } else if (i == 2)
                                {
                                    running = false;
                                    return 0;
                                }
                            }
                        }
                        }
                        else if (menu == HTP) {
                            if (CheckMouse(x, y, back_.GetRect())) {
                                    menu = INTRO;
                                }
                        }
                        else if (menu == CHOOSE)
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                if (CheckMouse(x, y, rect_choose[i]))
                                {
                                    if (i == 4) {
                                        menu = INTRO;
                                    }
                                    else {
                                        LoadBackGround(i);
                                        running = false;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = false;
                        return 0;
                    }
                default:
                {
                    break;
                }
            }
        }
		SDL_RenderPresent(g_screen);
		SDL_Delay(50);
	}
	return 1;
}

bool GameFunctions::LoadBackGround(const int& num)
{
    string img_background;
    switch(num)
    {
        case 0:
            img_background = "img//underwater.png";
            break;
        case 1:
            img_background = "img//sky.jpg";
            break;
        case 2:
            img_background = "img//universe.jpg";
            break;
        case 3:
            img_background = "img//city.png";
            break;
    }
    g_background = CommonFunc::LoadImage( img_background, g_screen);
    if (g_background == NULL) return false;
    return true;
}

void GameFunctions::CreateThreatList ()
{
    SharkList.push_back(new Shark);
    SharkList[SharkList.size()-1]->LoadImg("img//sharksheet.png", g_screen);
}

void GameFunctions::CreateBonusList()
{
    BonusList.push_back(new Bonus);
    BonusList[BonusList.size()-1]->SetType(rand()%3+1);
}

void GameFunctions::Replay()
{
    is_quit = false;
    bullet_ = rand()% 5 + 30;
    menu = INTRO;
    Score.SetValue(0);
    number_life.SetValue(LIFES);
    num_bullet.SetValue(bullet_);
    cat_obj.SetRect(0, SCREEN_HEIGHT/2 - CAT_HEIGHT/2);
    cat_obj.SetShownInjured(false);
    SharkList.clear();
    BonusList.clear();
    for (int i = 0; i < (int) BulletList.size(); i++)
    {
        BulletList[i]->SetIsMove(false);
    }
    BulletList.clear();
}
void GameFunctions::close()
{
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameFunctions::Run()
{
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    //Game play
    Mix_PlayMusic(background_, 10);
    is_quit = false;
    Bullet g_bullet;
    g_bullet.LoadImg("img//bullet.png", g_screen);
    g_bullet.SetRect(SCREEN_WIDTH-g_bullet.GetRect().w, 0);
    GameText max_bullet;
    max_bullet.LoadText(g_font, "/40", color_text, g_screen);
    max_bullet.SetRect(g_bullet.GetRect().x - 60, 0);
    num_bullet.SetRect(max_bullet.GetRect().x - 40, 0);
    Your_Score.LoadText(g_font, "Score:", color_text, g_screen);
    Your_Score.SetRect(0,0);
    Score.SetRect(120, 0);
    while(!is_quit) {
        frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&g_event))
        {
            switch (g_event.type) {
                case SDL_QUIT:
                    is_quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    is_quit = true;
                    break;
            }
            cat_obj.HandleInputAction(g_event, g_screen, cat_bullet, Score, number_life, num_bullet);
        }
        SDL_RenderClear(g_screen);
        SDL_RenderCopy(g_screen, g_background, NULL, &rect_screen);
        number_life.ShowNum(g_font, color_text, g_screen);
        heart.Show(g_screen);
        textX.Present(g_screen);
        Your_Score.Present(g_screen);
        Score.ShowNum(g_font, color_text, g_screen);
        if (num_bullet.GetValue() >= 40) {
            num_bullet.SetValue(40);
        }
        num_bullet.ShowNum(g_font, color_text, g_screen);
        g_bullet.Show(g_screen);
        max_bullet.Present(g_screen);
        if (Score.GetValue() >= 200 || number_life.GetValue() <= 2)
        {
            show_bullet.Present(g_screen);
        }
        //make bonus
        if (rand() %200 == 1) CreateBonusList();
		// Show Shark and Check Collision cat and shark
		if (Score.GetValue() < 500) {
                if (rand()%50 == 1) CreateThreatList();
            }
            else if(Score.GetValue() >= 500 && Score.GetValue() < 1600)
            {
                if (rand()%20 == 1) CreateThreatList();

            } else if (Score.GetValue() >= 1600 && Score.GetValue() <= 2500)
            {
                if (rand()%15 == 1) CreateThreatList();
            }
            else {
                if (rand()%10 == 1) CreateThreatList();
            }
        for(int i=0;i < (int)SharkList.size();i++)
        {
            if (Score.GetValue() < 500) {
                SharkList[i]->set_x_val(SHARK_SPEED1);
            }
            else if(Score.GetValue() >= 500 && Score.GetValue() < 1600)
            {
                SharkList[i]->set_x_val(SHARK_SPEED2);


            } else if (Score.GetValue() >= 1600 && Score.GetValue() <= 2500)
            {
                SharkList[i]->set_x_val(SHARK_SPEED3);
                SharkList[i]->set_y_val(5);
            }
            else
            {
                SharkList[i]->set_x_val(SHARK_SPEED4);
                SharkList[i]->set_y_val(10);
            }
            SharkList[i]->ShowSharkAnimation(g_screen);
            SharkList[i]->HandleMove();
            if (SharkList[i]->GetToIncreaseScore()) {
                if (cat_obj.GetRect().x >= SharkList[i]->GetRect().x+SharkList[i]->GetRect().w)
                {
                    Score.IncreaseValue(AVOID_SHARK_SCORE);
                    SharkList[i]->SetToIncreaseScore(false);
                }
            }
            //check collision main and threat
            bool check_coll = CommonFunc::CheckCollision(cat_obj.GetRect(), SharkList[i]->GetRect());
            if (check_coll) {
                cat_obj.SetShownInjured(true);
                number_life.IncreaseValue(-1);
                Score.IncreaseValue(INJURED_SCORE);
                Mix_PlayChannel(-1, injured_, 0);
                delete SharkList[i];
                SharkList.erase(SharkList.begin()+i);
            }
            if (SharkList[i]->GetRect().x < -SHARK_WIDTH) {
                SharkList[i]->Free();
            }
        }
        // check collision cat bullet and shark
        BulletList = cat_obj.GetBulletList();
		for (int b = 0; b < (int) BulletList.size(); b++)
		{
		    for (int s = 0; s < (int) SharkList.size(); s++)
            {
                bool check = CommonFunc::CheckCollision(SharkList[s]->GetRect(), BulletList[b]->GetRect());
                if (check)
                {
                    Score.IncreaseValue(KILL_SHARK_SCORE);
                    cat_obj.RemoveBullet(b);
                    delete SharkList[s];
                    SharkList.erase(SharkList.begin()+s);
                }
            }
		}
		// Manage Bonus List and cat
		for (int i=0;i<(int) BonusList.size();i++)
        {
            BonusList[i]->ShowBonus(g_screen);
            BonusList[i]->HandleMove();
            if (CommonFunc::CheckCollision(BonusList[i]->GetRect(), cat_obj.GetRect()) )
            {
                //update score and life
                switch (BonusList[i]->GetType())
                {
                    case 1:
                        Score.IncreaseValue(GET_BONUS_SCORE);
                        number_life.IncreaseValue(1);
                        if (number_life.GetValue() >= LIFES) {
                            number_life.SetValue(LIFES);
                        }
                        break;
                    case 2:
                        Score.IncreaseValue(GET_BONUS_SCORE);
                        num_bullet.IncreaseValue(1);
                        break;
                    case 3:
                        if (num_bullet.GetValue() < 40) {
                            num_bullet.IncreaseValue(2);
                        } else Score.IncreaseValue(GET_BONUS_SCORE);
                        break;
                }
                Mix_PlayChannel(-1,success_eat,0);
                delete BonusList[i];
                BonusList.erase(BonusList.begin()+i);
            }
        }
		if (number_life.GetValue()<=0) {
            is_quit= true;
            break;
		}
		//Show cat
        cat_obj.ControlBullet(g_screen);
        cat_obj.HandleMove();
        if(cat_obj.GetShowInjured()) {
            cat_obj.ShowInjured(g_screen);
        } else cat_obj.ShowAnimation(g_screen);
        SDL_RenderPresent(g_screen);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void GameFunctions::GetHighScore()
{
    ifstream read("text//HighScore.txt");// mo file HighScore de doc
    read >> high_score; // doc score trong file
    read.close(); // dong file
    if (Score.GetValue() > high_score) // neu score moi lon hon score cu duoc ghi trong file
    {
        high_score = Score.GetValue();// thi gan score trong file bang score moi
        ofstream file("text//HighScore.txt"); // mo file de ghi
        file << Score.GetValue(); // ghi lai score moi
        file.close();
    }
    High_Score.SetValue(high_score);// gan high score cho gametext
}

bool GameFunctions::ShowEnd() {
    cout << "Game Over!\n";
	is_quit = false;
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    Mix_PlayChannel(-1, s_game_over, 10);
    Game_over.LoadText(g_font_end, "GAME OVER", color_end, g_screen);
    Game_over.SetRect(SCREEN_WIDTH/2 - Game_over.GetRect().w/2 ,100);
    Your_Score.LoadText(g_font, "SCORE:  ", color_text, g_screen);
    Your_Score.SetRect(SCREEN_WIDTH/2-Your_Score.GetRect().w, Game_over.GetRect().y+ Game_over.GetRect().h+ 30);
    Score.SetRect(Your_Score.GetRect().x+Your_Score.GetRect().w+37, Your_Score.GetRect().y);
    High_ScoreText.LoadText(g_font, "HIGH SCORE:  ", color_text, g_screen);
    High_ScoreText.SetRect(SCREEN_WIDTH/2-High_ScoreText.GetRect().w, Score.GetRect().y+Score.GetRect().h + 10);
    GetHighScore();
    High_Score.SetRect(High_ScoreText.GetRect().x + High_ScoreText.GetRect().w + 37, High_ScoreText.GetRect().y);
    int x, y;
    GameText quit;
    bool selected = 0;
    quit.LoadText(g_font_intro, "QUIT", color_text, g_screen);
    quit.SetRect(SCREEN_WIDTH/2 - quit.GetRect().w/2, High_ScoreText.GetRect().y + High_ScoreText.GetRect().h+ 100);

    GameText home;
    home.LoadText(g_font_intro, "HOME", color_text, g_screen);
    home.SetRect(quit.GetRect().x, quit.GetRect().y - 40);
    SDL_ShowCursor(SDL_ENABLE);
    while (!is_quit)
    {
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type) {
                case SDL_QUIT:
                    is_quit = true;
                    return false;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE) {
                        is_quit = true;
                        return 0;
                    }
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    if (CheckMouse(x, y, quit.GetRect())) {
                        if (!selected)
                        {
                            selected = 1;
                            quit.LoadText(g_font_intro, "QUIT" , color_exit, g_screen);
                        }
                    }
                    else {
                        if (selected)
                        {
                            selected = 0;
                            quit.LoadText(g_font_intro, "QUIT", color_text, g_screen);
                        }
                    }
                    if (CheckMouse(x, y, home.GetRect())) {
                        home.LoadText(g_font_intro, "HOME" , color_select, g_screen);
                    }
                    else {
                        home.LoadText(g_font_intro, "HOME", color_text, g_screen);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    if (CheckMouse(x, y, quit.GetRect()))
                    {
                        is_quit = true;
                        return 0;

                    }
                    if (CheckMouse(x, y, home.GetRect()))
                    {
                        is_quit = true;
                        return 1;
                    }
            }
        }
        SDL_RenderCopy(g_screen, g_background, NULL, &rect_screen);
        Game_over.Present(g_screen);
        Your_Score.Present(g_screen);
        Score.ShowNum(g_font, color_text,g_screen) ;
        High_ScoreText.Present(g_screen);
        High_Score.ShowNum(g_font, color_text, g_screen);
        home.Present(g_screen);
        quit.Present(g_screen);
        SDL_RenderPresent(g_screen);
        SDL_Delay(35);
    }
	close();
	return 0;
}
