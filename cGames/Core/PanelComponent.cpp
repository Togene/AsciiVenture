void PanelComponent::RenderPanel(RenderEngine *Renderer)
{
    PanelComponent p = *this;
    Vector2 pos = this->object->t.GetWorldPosition();

    for (int x = 0; x < p.GetSize().x; x++)
    {
        for (int y = 0; y < p.GetSize().y; y++)
        {
            CHAR_INFO att;
            int mIndexY = (y + (int)pos.y);
            int mIndexX = (x + (int)pos.x);
            int mIndex = (mIndexY)*Renderer->GetScreenWidth() + mIndexX;

            if (mIndexX >= Renderer->GetScreenWidth() || mIndexX < 0 || mIndexY >= Renderer->GetScreenWidth() || mIndexY < 0)
            {
                continue;
            }
            else
            {
                att.Char.UnicodeChar = ' ';
                att.Attributes = p.GetColor();
            }

            Renderer->SetScreenCharAt(mIndex, att);
        }
    }

    if (this->object->GetChildren().size() != 0)
    {
        for (int i = 0; i < this->object->GetChildren().size(); i++)
        {
            RenderChildren(i, Renderer);
        }
    }
}

void PanelComponent::CheckInteractions(RenderEngine *Renderer, float mX, float mY, bool clicked)
{
    if (Getinteractive())
        InteractWithElement(*this, mX, mY, clicked);

    if (this->object->GetChildren().size() != 0)
    {
        for (int i = 0; i < this->object->GetChildren().size(); i++)
        {
            HandleChildInterAction(i, Renderer, mX, mY, clicked);
        }
    }
}

void PanelComponent::RenderChildren(int i, RenderEngine *Renderer)
{
    if (this->object->GetChildAt(i)->GetComponent<PanelComponent>() != nullptr)
    {
        this->object->GetChildAt(i)->GetComponent<PanelComponent>()->RenderPanel(Renderer);
    }
    if (this->object->GetChildAt(i)->GetComponent<TextComponent>() != nullptr)
    {
        this->object->GetChildAt(i)->GetComponent<TextComponent>()->RenderText(Renderer, this->GetSizeRef());
    }
    if (this->object->GetChildAt(i)->GetComponent<cUISpriteComponent>() != nullptr)
    {
        this->object->GetChildAt(i)->GetComponent<cUISpriteComponent>()->RendercSprite(Renderer);
    }
    if (this->object->GetChildAt(i)->GetComponent<SliderComponent>() != nullptr)
    {
        this->object->GetChildAt(i)->GetComponent<SliderComponent>()->RenderSlider(Renderer);
    }
    if (this->object->GetChildAt(i)->GetComponent<CheckBoxComponent>() != nullptr)
    {
        this->object->GetChildAt(i)->GetComponent<CheckBoxComponent>()->RenderCheckBox(Renderer);
    }
}

void PanelComponent::HandleChildInterAction(int i, RenderEngine *Renderer, float mX, float mY, bool clicked)
{
    if (this->object->GetChildAt(i)->GetComponent<PanelComponent>() != nullptr)
    {
        this->object->GetChildAt(i)->GetComponent<PanelComponent>()->CheckInteractions(Renderer, mX, mY, clicked);
    }
    else if (this->object->GetChildAt(i)->GetComponent<TextComponent>() != nullptr)
    {
        InteractWithElement(*this->object->GetChildAt(i)->GetComponent<TextComponent>(), mX, mY, clicked);
    }
    else if (this->object->GetChildAt(i)->GetComponent<cUISpriteComponent>() != nullptr)
    {
        InteractWithElement(*this->object->GetChildAt(i)->GetComponent<cUISpriteComponent>(), mX, mY, clicked);
    }
    else if (this->object->GetChildAt(i)->GetComponent<SliderComponent>() != nullptr)
    {
        InteractWithElement(*this->object->GetChildAt(i)->GetComponent<SliderComponent>(), mX, mY, clicked);
    }
    else if (this->object->GetChildAt(i)->GetComponent<CheckBoxComponent>() != nullptr)
    {
        InteractWithElement(*this->object->GetChildAt(i)->GetComponent<CheckBoxComponent>(), mX, mY, clicked);
    }
}

//Heads Up, Rectangles are rendered from pos -> to max size
//doesnt start from centre so /2.0 work work

void PanelComponent::InteractWithElement(PanelComponent &p, float mX, float mY, bool clicked)
{
    p.HoverOver(mX, mY, clicked);
}

void PanelComponent::InteractWithElement(TextComponent &t, float mX, float mY, bool clicked)
{
    t.HoverOver(mX, mY, clicked, this);
}

void PanelComponent::InteractWithElement(cUISpriteComponent &c, float mX, float mY, bool clicked)
{
    c.HoverOver(mX, mY, clicked);
}

void PanelComponent::InteractWithElement(SliderComponent &sl, float mX, float mY, bool clicked)
{
    sl.HoverOver(mX, mY, clicked);
}

void PanelComponent::InteractWithElement(CheckBoxComponent &bx, float mX, float mY, bool clicked)
{
    bx.HoverOver(mX, mY, clicked);
}

void PanelComponent::RenderBackGround(RenderEngine *Renderer)
{
    PanelComponent p = *this;
    Vector2 pos = this->object->t.GetWorldPosition();

    for (int nx = 0; nx < p.GetSize().x; nx++)
        for (int ny = 0; ny < p.GetSize().y; ny++)
        {
            CHAR_INFO att;

            att.Char.UnicodeChar = ' ';
            att.Attributes = p.GetColor();
            Renderer->SetScreenCharAt((ny + pos.y) * Renderer->GetScreenWidth() + (nx + pos.x), att);
        }
}