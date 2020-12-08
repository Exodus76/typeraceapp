use cursive::event::{Key};
use cursive::align::HAlign;
use cursive::views::{Dialog, EditView, ResizedView, TextView, LinearLayout, ProgressBar};
use cursive::traits::*;
use cursive::Cursive;
use cursive::menu::MenuTree;
use cursive::views::PaddedView;

use std::sync::Once;

use cursive::{
    theme::{Effect, Style},
    utils::markup::StyledString,
    views,
};

// This example define a custom view that prints any event it receives.
// This is a handy way to check the input received by cursive.
//add a

// content: vec<&str> = "just as I'm giving up, my heart is palpitating. Here comes another one, it's so intoxicating. And being where I've been, I know that in the end I'll do it all again.".split(" ").collect();

#[warn(unused_imports)]
fn main() {
    let mut siv = cursive::default();

    siv.menubar()
        .add_subtree(
            "Edit",
            MenuTree::new()
                    .leaf("name", move |s|{
                        s.menubar().find_subtree("Edit").unwrap();
                    })
        )
        .add_subtree(
            "Help",
            MenuTree::new()
                    .leaf("About", |s| {
                        s.add_layer(Dialog::info("created by a anon pajeet"))
                    })
        )
        .add_delimiter()
        .add_leaf("Quit", |s| s.quit());

    siv.add_layer( Dialog::new()
                .title("gib name")
                .content(
                    EditView::new()
                        .on_submit(racing_screen)
                        .with_name("username")
                )
                .button("Ok",|s| {
                    let name = s.call_on_name("username", |view: &mut EditView| {
                        view.get_content() //get the input
                    })
                    .unwrap();
                    racing_screen(s, &name);
                }),
    );
    // siv.add_layer(Dialog::text("again"));

    siv.add_global_callback(Key::Esc, |s| s.select_menubar());
    // siv.select_menubar();

    // siv.set_autohide_menu(false);

    siv.run();
}

fn racing_screen(s: &mut Cursive, name: &str)
{
    if name.is_empty()
    {
        s.add_layer(Dialog::info("You forgot gib name"));
    } else {
        s.pop_layer();

        let type_text = "Isn't that cool";

        let text : Vec<&str> = type_text.split_whitespace().collect();
        let mut styled = StyledString::plain("");
        
        for i in text {
            styled.append(StyledString::plain(i));
            styled.append(" ");
        }

        let racing_text = ResizedView::with_max_width(80, 
            Dialog::new()
            .content(

                TextView::new(styled).with_name("1"),
            )
            .h_align(HAlign::Left)
        );

        let typing_field = ResizedView::with_max_width(80, EditView::new().on_edit(on_edit));


        let userinfo = ResizedView::with_max_width(80, 
            Dialog::new()
            .content(
                LinearLayout::horizontal()
                    .child( PaddedView::lrtb(0, 3, 0 , 0 , TextView::new(name)) )
                    .child(
                        ProgressBar::new()
                                .with_task(|counter| {
                                    for _ in 0..100 {
                                        counter.tick(1);
                                    }
                                }),
                    ),
            )
            .h_align(HAlign::Left)
        );
        s.set_autorefresh(false);
        s.add_layer(
            LinearLayout::vertical()
            .child(racing_text)
            .child(typing_field)
            .child(userinfo)
        );
    }
}

static START: Once = Once::new();

fn on_edit(s: &mut cursive::Cursive, edit_text: &str, _cursor: usize) {

    START.call_once(||{
        s.add_layer(Dialog::info("created by a anon pajeet"));
    });

    s.call_on_name("1", |t: &mut views::TextView| {
    
        let mut new_content = StyledString::new();
        for span in t.get_content().spans() {
            let new_style = if edit_text == span.content {
                Style::from(Effect::Bold)
            } else {
                // `span.attr` here is the `&Style` applied to the span
                *span.attr
            };
            // `span.content` here is the visible text for this span.   
            new_content.append_styled(span.content, new_style);
        }
        t.set_content(new_content);
    });
}


// when mouseclick on the edit text start the race
// when the value in race matches the value with the respective indexed content color the content and clear the edit text
