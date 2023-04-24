#include "GameFunctions.h"

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
        selected_ = Mix_LoadWAV("sound//meow.mp3");
        injured_ = Mix_LoadWAV("sound//injured.wav");
        cat_bullet = Mix_LoadWAV("sound//meow.mp3");
        success_eat = Mix_LoadWAV("sound//eat_fish.mp3");
        s_game_over = Mix_LoadWAV("sound//game_over.mp3");
        if (background_ == NULL || intro_ == NULL || injured_ == NULL||cat_bullet == NULL
            ||success_eat == NULL|| s_game_over == NULL)
        {
            cout << "Fail to load sound";
            return false;
        }
        if (TTF_Init() == -1) return false;
        g_font = TTF_OpenFont("PressStart2P.ttf", 20);
        g_font_intro = TTF_OpenFont("PressStart2P.ttf", 30);
        g_font_end = TTF_OpenFont("PressStart2P.ttf", 77);
        g_font_choose = TTF_OpenFont("Quantico.ttf", 50);
        if (g_font == NULL) {
            cout << "Fail to load font";
            return false;
        }
    }
	return true;
}

bool GameFunctions::CheckMouse(int &x, int &y, SDL_Rect rect_mouse)
{
    if (x >=rect_mouse.x && x <= rect_mouse.x+rect_mouse.w
        && y >= rect_mouse.y && y <= rect_mouse.y+rect_mouse.h)
        return true;
    return false;
}

int GameFunctions::ShowIntro()
{
    SDL_Rect rect_bg_intro = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    LTexture bg_intro(g_screen, rect_bg_intro);
    bg_intro.loadFromFile("img//intro.jpg");

    SDL_Rect rect_sound = {10, 10, 29, 24};
    LTexture sound_(g_screen, rect_sound);
    sound_.loadFromFile("img//sound.png");
    bool select_sound = 0;

    Mix_PlayMusic(intro_ , 10);

    const int text_n = 3;
    GameText intro_t[text_n];
    string text[text_n] = {"Play", "How To Play", "Exit" };
    SDL_Rect rect_intro[text_n];
    bool selected[text_n] = {0, 0, 0};
    for (int i = 0; i < text_n; i++) {
        intro_t[i].LoadText(g_font_intro, text[i], color_intro, g_screen);
        intro_t[i].SetRect(100, 200 + 70*i);
        rect_intro[i] = intro_t[i].GetRect();
    }

	int x, y;
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event))
		{
			switch (g_event.type)
			{
                case SDL_QUIT:
                {
                    is_quit = true;
                    return 2;
                }
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    for (int i = 0; i < text_n; i++)
                    {
                        if (CheckMouse(x, y, rect_intro[i]))
                        {
                            if (!selected[i])
                            {
                                Mix_PlayChannel(-1, cat_bullet, 0);
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
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = g_event.button.x;
                    y = g_event.button.y;
                    if (CheckMouse(x, y, rect_sound)) {
                        if (!select_sound) {
                            select_sound = 1;
                            Mix_VolumeMusic(0);
                            Mix_VolumeChunk(selected_, 0);
                            Mix_VolumeChunk(cat_bullet, 0);
                            Mix_VolumeChunk(s_game_over, 0);
                            sound_.loadFromFile("img//mute.png");
                        }
                        else{
                            select_sound = 0;
                            Mix_VolumeMusic(MIX_MAX_VOLUME);
                            Mix_VolumeChunk(selected_, MIX_MAX_VOLUME);
                            Mix_VolumeChunk(cat_bullet, MIX_MAX_VOLUME);
                            Mix_VolumeChunk(s_game_over, MIX_MAX_VOLUME);
                            sound_.loadFromFile("img//sound.png");
                        }
                    }
                    for (int i = 0; i < text_n; i++)
                    {
                        if (CheckMouse(x, y, rect_intro[i]))
                        {
                            return i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 2;
                    }
                default:
                {
                    break;
                }
            }
        }
        SDL_RenderClear(g_screen);

		bg_intro.render();
		sound_.render();

		for (int i = 0; i < text_n; i++)
		{
            intro_t[i].Present(g_screen);
		}
		SDL_RenderPresent(g_screen);
	}

	return 2;
}

int GameFunctions::ChooseBackGround()
{
    bool running = true;
    SDL_Rect rect_bg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    LTexture bg(g_screen, rect_bg);
    bg.loadFromFile("img//intro.jpg");

    GameText chooseBgText;
    chooseBgText.LoadText(g_font_choose, "CHOOSE GAME BACKGROUND", color_intro, g_screen);
    chooseBgText.SetRect(SCREEN_WIDTH/2 - chooseBgText.GetRect().w/2, 100);
    GameText choose_bg[5];
    int x, y;
    string text[5] = {"Underwater", "Sky", "Universe", "Ground", "Exit"};
    SDL_Rect rect_choose[5];

    bool selected[5] = {0, 0, 0, 0 ,0};
    for (int i = 0; i < 5; i++) {

        choose_bg[i].LoadText(g_font, text[i], color_intro, g_screen );
        choose_bg[i].SetRect(100, 200+i*50);
        rect_choose[i] = choose_bg[i].GetRect();
    }
    while(running)
    {
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
                case SDL_QUIT:
                    running = false;
                    return 4;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = false;
                    }
                    return 4;
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    for (int i = 0; i < 5; i++)
                    {
                        if (CheckMouse(x, y, rect_choose[i]))
                        {
                            if (!selected[i])
                            {
                                Mix_PlayChannel(-1, selected_, 0);

                                selected[i] = 1;
                                if (i == 4) {
                                    choose_bg[i].LoadText(g_font_intro, text[i], color_exit, g_screen);
                                } else {
                                choose_bg[i].LoadText(g_font_intro, text[i], color_select, g_screen);
                                }
                            }
                        }
                        else
                        {
                            if (selected[i])
                            {
                                selected[i] = 0;
                                choose_bg[i].LoadText(g_font, text[i], color_intro, g_screen);
                            }
                        }
                    }

                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    for (int i = 0; i < 5; i++)
                    {
                        if (CheckMouse(x, y, rect_choose[i]))
                        {
                            return i;
                        }
                    }
            }
        }

        SDL_RenderClear(g_screen);
        bg.render();
        chooseBgText.Present(g_screen);
        for (int i = 0; i < 5; i++) {
            choose_bg[i].Present(g_screen);
        }
        SDL_RenderPresent(g_screen);

    }
    return 4;
}

bool GameFunctions::LoadBackGround(const int& num)
{
    string img_background;
    switch(num)
    {
        case 0:
            img_background = "img//bg_underwater.png";
            break;
        case 1:
            img_background = "img//bg_sky.jpg";
            break;
        case 2:
            img_background = "img//bg_universe.jpg";
            break;
        case 3:
            img_background = "img//bg_ground.jpg";
            break;
    }
    bool check_loadbg = g_background.LoadImg(img_background, g_screen);
    if (check_loadbg == false) {
        cout << "Couldn't find image\n";
        return false;
    }
    return true;
}

void GameFunctions::GetHighScore()
{
    ifstream read("HighScore.txt");// mo file HighScore de doc
    read >> high_score; // doc so trong file
    read.close(); // dong file
    if (Score.GetValue() > high_score) // neu score moi lon hon score cu duoc ghi trong file
    {
        high_score = Score.GetValue();// thi gan score trong file bang score moi
        ofstream file("HighScore.txt"); // mo file de ghi
        file << Score.GetValue(); // ghi lai score moi
        file.close();
    }
    High_Score.SetValue(high_score);// gan high score cho gametext
}
void GameFunctions::InitEnd()
{
    text_g_o.LoadText(g_font_end, "GAME OVER", color_end, g_screen);
    text_g_o.SetRect(SCREEN_WIDTH/2 - text_g_o.GetRect().w/2 ,SCREEN_HEIGHT/2-text_g_o.GetRect().h - 50);

    Your_Score.LoadText(g_font, "SCORE:  ", color_text, g_screen);
    Your_Score.SetRect(SCREEN_WIDTH/2-Your_Score.GetRect().w, text_g_o.GetRect().y+ text_g_o.GetRect().h+ 30);
    Score.SetRect(Your_Score.GetRect().x+Your_Score.GetRect().w+37, Your_Score.GetRect().y);

    High_ScoreText.LoadText(g_font, "HIGH SCORE:  ", color_text, g_screen);
    High_ScoreText.SetRect(SCREEN_WIDTH/2-High_ScoreText.GetRect().w, Score.GetRect().y+Score.GetRect().h + 10);
    GetHighScore();
    High_Score.SetRect(High_ScoreText.GetRect().x + High_ScoreText.GetRect().w + 37, High_ScoreText.GetRect().y);
}

void GameFunctions::InitLife()
{
    heart.LoadImg("img//heart.png", g_screen);
    heart.SetWidth(40, 25);
    heart.SetRect(SCREEN_WIDTH/2 - heart.GetRect().w, 0);

    textX.LoadText(g_font, "x", color_text, g_screen);
    textX.SetRect(SCREEN_WIDTH/2 - heart.GetRect().w + 50, heart.GetRect().h/2-textX.GetRect().h/2);

    number_life.SetValue(LIFES);
    number_life.SetRect(SCREEN_WIDTH/2 - heart.GetRect().w+50+heart.GetRect().w, heart.GetRect().h/2-textX.GetRect().h/2);
}

void GameFunctions::ShowLife()
{
    number_life.ShowNum(g_font, color_text, g_screen);
    heart.Show(g_screen);
    textX.Present(g_screen);
}
void GameFunctions::CreateThreatList ()
{
    for (int i = 0; i < SHARK_NUM; i++) {
        SharksList.push_back(new Shark());

        int shark_y = rand() % 400;
        SharksList[i]->SetRect(SCREEN_WIDTH + 400*i, shark_y);
        SharksList[i]->SetAnimation();
        }
}

vector<Shark*> GameFunctions::MakeThreatList()
{
	std::vector<Shark*> list_threats;// static threat


	Shark* dynamic_threats = new Shark[20];
	for (int i = 0; i < 20; i++)
	{
		Shark* p_threat = (dynamic_threats + i);
		if (p_threat != NULL)
		{
			int shark_y = rand() % (SCREEN_HEIGHT-p_threat->GetRect().h) + 10;
            p_threat->SetRect(SCREEN_WIDTH + 400*i, shark_y);
			p_threat->SetAnimation();
			list_threats.push_back(p_threat);
		}
	}
	return list_threats;
}
void GameFunctions::close()
{
	g_background.Free();
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
    srand(time(NULL));
    is_quit = false;
    rect_screen.x = 0;
    rect_screen.y = 0;
    rect_screen.w = SCREEN_WIDTH;
    rect_screen.h = SCREEN_HEIGHT;
	// Show intro
    int check_show = ShowIntro();

    if (check_show == 2)
    {
        is_quit = true;
        return ;
    }
    if (check_show == 0)
    {
        int choose = ChooseBackGround();
        switch(choose)
        {
            case 0:
                LoadBackGround(0);
                break;
            case 1:
                LoadBackGround(1);
                break;
            case 2:
                LoadBackGround(2);
                break;
            case 3:
                LoadBackGround(3);
                break;
            case 4:
                is_quit = true;
                return;
        }
    }
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    Mix_PlayMusic(background_, 10);
    //Game play
    is_quit = false;
    InitLife();
    SharksList = MakeThreatList();
    Score.SetRect(0, 0);
    SDL_Rect rect_close = {800-25, 0, 25, 25};
    LTexture close_button(g_screen, rect_close);
    close_button.loadFromFile("img//close.png");
    while(!is_quit) {

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
                case SDL_MOUSEMOTION:{
                    int x = g_event.motion.x;
                    int y = g_event.motion.y;
                    if (CheckMouse(x, y, rect_close)) {
                        close_button.setColor(255, 0, 0);
                    } else close_button.setColor(255, 255, 255);
                }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int x = g_event.motion.x;
                    int y = g_event.motion.y;
                    if (CheckMouse(x, y, rect_close)) {
                        is_quit = true;
                        return ;
                    }
            }
            cat_obj.HandleInputAction(g_event, g_screen, cat_bullet);
        }
        frameStart = SDL_GetTicks();
		SDL_RenderClear(g_screen);

        g_background.ShowBackground(g_screen);
        close_button.render();
        ShowLife();
        cat_obj.ControlBullet(g_screen);
        cat_obj.ShowAnimation(g_screen);
        cat_obj.HandleMove();
        Score.ShowNum(g_font, color_text, g_screen);

        for(int i=0;i < (int)SharksList.size();i++)
        {
            Shark* obj_threat = SharksList.at(i);
            if (Score.GetValue() >= 0 && Score.GetValue() <= 800) {
                obj_threat->set_x_val(SPEED_THREAT1);
            }
            else if(Score.GetValue() > 800 && Score.GetValue() <= 1000)
            {
                obj_threat->set_x_val(SPEED_THREAT2);

            } else if (Score.GetValue() > 1000)
            {
                if (rand()%40 == 1) {
                    obj_threat->set_x_val(SPEED_THREAT3);
                    obj_threat->set_y_val(SPEED_THREAT2);
                } else if (rand()%40 == 0)
                {
                    obj_threat->set_x_val(SPEED_THREAT3);
                    obj_threat->set_y_val(-SPEED_THREAT3);
                }
            }

            obj_threat->ShowSharkAnimation(g_screen);
            obj_threat->HandleMove();
            //check collision main va threat
            bool check_coll = CommonFunc::CheckCollision(cat_obj.GetRect(), SharksList[i]->GetRect());
            if (check_coll) {
                obj_threat->Free();
                obj_threat->Reset(SCREEN_WIDTH+ 10*i);

                number_life.IncreaseValue(-1);

                Score.IncreaseValue(INJURED_SCORE);
                Mix_PlayChannel(-1, injured_, 0);
            }

        }
        std::vector<Bullet*> bullet_arr = cat_obj.GetBulletList();
		for (int r = 0; r < (int) bullet_arr.size(); r++)
		{
			Bullet* p_bullet = bullet_arr.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < (int) SharksList.size(); t++)
				{
					Shark* obj_threat = SharksList.at(t);
					if (obj_threat != NULL)
					{
						SDL_Rect tRect = obj_threat->GetRect();
						SDL_Rect bRect = p_bullet->GetRect();
						bool bCol = CommonFunc::CheckCollision(bRect, tRect);

						if (bCol)
						{
							cat_obj.RemoveBullet(r);
							Score.IncreaseValue(KILL_SHARK_SCORE);
							obj_threat->Reset(SCREEN_WIDTH+20*t);
						}
					}
				}
			}
		}

		if (number_life.GetValue()<=0) is_quit= true;
		 SDL_RenderPresent(g_screen);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    for (int i = 0; i < (int) SharksList.size(); i++)
	{
		Shark* p_threat = SharksList.at(i);
		if (p_threat != NULL)
		{
			p_threat->Free();
			p_threat = NULL;
		}
	}

	is_quit = false;
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    InitEnd();
    Mix_PlayChannel(-1, s_game_over, 10);
    int x, y;
    GameText quit;
    bool selected = 0;
    quit.LoadText(g_font, "QUIT", color_text, g_screen);
    quit.SetRect(SCREEN_WIDTH/2- quit.GetRect().w/2, High_ScoreText.GetRect().y + High_ScoreText.GetRect().h+ 50);

    while (!is_quit)
    {
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type) {
                case SDL_QUIT:
                    is_quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE) {
                        is_quit = true;
                        return ;
                    }
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    if (CheckMouse(x, y, quit.GetRect())) {
                        if (!selected)
                        {
                            Mix_PlayChannel(-1, selected_, 0);
                            selected = 1;
                            quit.LoadText(g_font, "QUIT" , color_end, g_screen);
                        }
                    }
                    else {
                        if (selected)
                        {
                            selected = 0;
                            quit.LoadText(g_font, "QUIT", color_text, g_screen);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:{
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    if (CheckMouse(x, y, quit.GetRect()))
                    {
                        is_quit = false;
                        return ;
                    }
                    }
            }
        }
        g_background.ShowBackground(g_screen);
        text_g_o.Present(g_screen);
        Your_Score.Present(g_screen);
        Score.ShowNum(g_font, color_text,g_screen) ;
        High_ScoreText.Present(g_screen);
        High_Score.ShowNum(g_font, color_text, g_screen);
        quit.Present(g_screen);
        SDL_RenderPresent(g_screen);
        SDL_Delay(35);
    }
	SharksList.clear();
    close();
}
